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
		memcpy_s(result->message, template_name_length, template_name, template_name_length);
		result->message[template_name_length] = 0;
		exit__parse();
	}

	bool alloc_error = false;

	if (!depth && template->lines.length) {
		listClear(template->lines);
		listCreate(template->lines, Line, 16, alloc_error);
		if (alloc_error) {
			exit__parse();
		}
	}

	Line *line;
	listGetNew(template->lines, Line, line, alloc_error);
	if (alloc_error) {
		exit__parse();
	}
	initLine(*line);

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	size_t cs;

	%%{

		action action_start_line { line->tokens.line.start = p; }
		action action_end_line {

			line->tokens.line.end = p;

			verifyAction(*line);
			computeTokensLengths(*line);
			computeOther(*line);

			if (line->action != ACTION_NONE) {
				drunk_malloc_one__parse(line->tokens.name.copy, sizeof(char) * (line->tokens.name.length + 1));
				memcpy(line->tokens.name.copy, line->tokens.name.start, line->tokens.name.length);
				line->tokens.name.copy[line->tokens.name.length] = 0;
			}

			listGetNew(template->lines, Line, line, alloc_error);
			if (alloc_error) {
				exit__parse();
			}
			initLine(*line);

		}

		action action_param { line->action = ACTION_PARAM; }
		action action_ref { line->action = ACTION_REF; }
		action action_optional { line->flags.optional = true; }
		action action_strict { line->flags.strict = true; }

		action action_start_name { line->tokens.name.start = p; }
		action action_end_name { line->tokens.name.end = p; }

		action action_start_expression {
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
		action action_end_expression { line->tokens.expression.end = p; }
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

};


parse_result parse(char *name) {

	parse_result result;
	result.code = 0;
	result.message = NULL;

	_parse(name, strlen(name), 0, &result);

	return result;

}