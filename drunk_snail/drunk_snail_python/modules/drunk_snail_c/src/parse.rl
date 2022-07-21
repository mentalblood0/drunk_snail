#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdbool.h>
#include <sys/types.h>

#include "../modules/List/include/List.h"
#include "../modules/memoma/include/memoma.h"
#include "../modules/prefix_tree/include/prefix_tree.h"

#include "../include/Line.h"
#include "../include/Other.h"
#include "../include/Template.h"
#include "../include/templates.h"

#include "../include/parse.h"



%%{
	machine parse_python;
	write data;
}%%



#define exit__parse() {\
	result->code = 1;\
	return;\
}


#define drunk_malloc_one__parse(target, size) {\
	target = malloc(size);\
	if (!target) {\
		exit__parse();\
	}\
}


#define drunk_realloc_one__parse(target, size, temp) {\
	if (size) {\
		temp = realloc(target, size);\
		if (!temp) {\
			exit__parse();\
		} else {\
			target = temp;\
		}\
	}\
}


#define allocNewLine(target, list, alloc_error) {\
	listGetNew(list, Line, target, alloc_error);\
	if (alloc_error) {\
		exit__parse();\
	}\
	initLine(*target);\
}


void _parse(
	char *template_name,
	size_t template_name_length,
	size_t depth,
	parse_result *result
)
{

	Template *template = dictionaryLookupUnterminated(templates, template_name, template_name_length);
	if (template == NULL) {
		drunk_malloc_one__parse(result->message, sizeof(char) * (template_name_length + 1));
		memcpy(result->message, template_name, template_name_length);
		result->message[template_name_length] = 0;
		exit__parse();
	}

	bool alloc_error = false;

	if (!depth && template->lines.length) {
		listFree(template->lines);
		listCreate(template->lines, Line, 16, alloc_error);
		if (alloc_error) {
			exit__parse();
		}
	}

	Line *line;
	allocNewLine(line, template->lines, alloc_error);

	Expression *current_expression = &line->single_expression;

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	size_t cs;

	%%{

		action action_start_line { line->line.start = p; }
		action action_end_line {

			line->line.end = p;

			verifyAction(*line);
			computeLineTokensLengths(*line);
			computeOther(*line);

			if (line->action == ACTION_NONE) {
				if (
					(template->lines.length >= 2) &&
					(template->lines.start[template->lines.length - 2].action == ACTION_NONE)
				) {
					template->lines.start[template->lines.length - 2].line.length += 1 + line->line.length;
					resetLine(*line);
				} else {
					allocNewLine(line, template->lines, alloc_error);
				}
			} else {
				allocNewLine(line, template->lines, alloc_error);
			}

			current_expression = &line->single_expression;

		}

		action action_param { line->action = ACTION_PARAM; }
		action action_ref { line->action = ACTION_REF; }
		action action_optional { current_expression->flags.optional = true; }
		action action_strict { current_expression->flags.strict = true; }

		action action_start_name { current_expression->tokens.name.start = p; }
		action action_end_name { current_expression->tokens.name.end = p; }

		action action_start_expression {
			if (!(current_expression->tokens.expression.start && current_expression->tokens.name.end))
				current_expression->tokens.expression.start = p;
		}
		action action_end_expression {

			current_expression->tokens.expression.end = p;

			if (current_expression->tokens.name.start) {

				computeExpressionTokensLengths(*current_expression);

				drunk_malloc_one__parse(current_expression->tokens.name.copy, sizeof(char) * (current_expression->tokens.name.length + 1));
				memcpy(current_expression->tokens.name.copy, current_expression->tokens.name.start, current_expression->tokens.name.length);
				current_expression->tokens.name.copy[current_expression->tokens.name.length] = 0;

			}

			if (line->action == ACTION_PARAM) {

				if (!line->param_expressions) {
					line->param_expressions = malloc(sizeof(ExpressionList));
					if (!line->param_expressions) {
						exit__parse();
					}
					listCreate(*(line->param_expressions), Expression, 4, alloc_error);
					if (alloc_error) {
						exit__parse();
					}
					listExtend(*(line->param_expressions), Expression, alloc_error);
					if (alloc_error) {
						exit__parse();
					}
					line->param_expressions->start[0] = *current_expression;
				} else {
					if (line->param_expressions->length) {
						line->action = ACTION_PARAM_MULTI;
					}
				}
				listGetNew(*(line->param_expressions), Expression, current_expression, alloc_error);
				if (alloc_error || !current_expression) {
					exit__parse();
				}
				initExpression(*current_expression);

			} else if (line->param_expressions) {
				if (line->param_expressions->length) {
					line->action = ACTION_NONE;
				}
			}

		}
		action action_end_expressions { line->has_expressions = true; }

		open = '<!--';
		close = '-->';

		delimeter = '\n';
		other = (any - delimeter)+;

		param = '(param)' %action_param;
		ref = '(ref)' %action_ref;
		type = param | ref;

		optional = '(optional)' %action_optional;
		strict = '(strict)' %action_strict;
		flag = optional | strict;

		name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_start_name %action_end_name;

		param_expression = (open ' '* flag? param name ' '* close) >action_start_expression %action_end_expression;
		ref_expression = (open ' '* flag? ref name ' '* close) >action_start_expression %action_end_expression;

		expressions = ((param_expression other?)+ | (ref_expression other?)) %action_end_expressions;

		line = (other? expressions?) >action_start_line %action_end_line;

		template = (line delimeter)* (line - zlen)?;
		main := template;

		write init;
		write exec;

	}%%

	template->lines.length -= 1;
	if (template->lines.length) {
		if (template->lines.start[template->lines.length-1].param_expressions) {
			template->lines.start[template->lines.length-1].param_expressions->length -= 1;
		}
	}

};


parse_result parse(char *name) {

	parse_result result;
	result.code = 0;
	result.message = NULL;

	_parse(name, strlen(name), 0, &result);

	return result;

}