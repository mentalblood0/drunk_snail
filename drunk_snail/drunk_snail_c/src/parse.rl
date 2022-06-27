#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "../include/ParseResult.h"



%%{
	machine parse;
	write data;
}%%



#define exit_parse_() {\
	parse_result->code = 1;\
	return;\
}


#define drunk_malloc_one_parse_(target, size) {\
	target = malloc(size);\
	if (!target) {\
		exit_parse_();\
	}\
}


#define drunk_realloc_one_parse_(target, size, temp) {\
	if (size) {\
		temp = realloc(target, size);\
		if (!temp) {\
			exit_parse_();\
		} else {\
			target = temp;\
		}\
	}\
}


void parse__(
	char *template_name,
	size_t template_name_length,
	size_t depth,
	ParseResult *parse_result
)
{

	Template *template = dictionaryLookupUnterminated(templates, template_name, template_name_length);
	if (template == NULL) {
		drunk_malloc_one_parse_(parse_result->message, sizeof(char) * (template_name_length + 1));
		memcpy_s(parse_result->message, template_name_length, template_name, template_name_length);
		parse_result->message[template_name_length] = 0;
		exit_parse_();
	}

	size_t i;
	bool alloc_error = false;

	if (!depth && template->lines.length) {
		listClear(template->lines, i);
		listCreate(template->lines, 16, alloc_error);
		if (alloc_error) {
			exit_parse_();
		}
	}

	Line *line = NULL;

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	size_t cs;

	drunk_malloc_one_parse_(line, sizeof(Line));
	initLine(*line);

	%%{

		action action_start_line { line->tokens.line.start = p; }
		action action_end_line {

			line->tokens.line.end = p;
			listPush(template->lines, line, alloc_error);
			if (alloc_error) {
				free(line);
				exit_parse_();
			}

			verifyAction(*line);
			computeTokensLengths(*line);

			if (line->action != ACTION_NONE) {
				drunk_malloc_one_parse_(line->tokens.name.copy, sizeof(char) * (line->tokens.name.length + 1));
				memcpy(line->tokens.name.copy, line->tokens.name.start, line->tokens.name.length);
				line->tokens.name.copy[line->tokens.name.length] = 0;
			}

			drunk_malloc_one_parse_(line, sizeof(Line));
			initLine(*line)

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

		prefix = flag* type flag*;
		name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_start_name %action_end_name;

		expression = (open ' '* prefix name ' '* close) >action_start_expression %action_end_expression;

		line = (other? expression? other?) >action_start_line %action_end_line;

		template = (line delimeter)* (line - zlen)?;
		main := template;

		write init;
		write exec;

	}%%

	free(line);

};


PyObject* parse_(char *name) {

	ParseResult result;
	result.code = 0;
	result.message = NULL;

	parse__(name, strlen(name), 0, &result);

	if (result.code) {
		if (result.message) {
			PyErr_SetString(PyExc_KeyError, result.message);
		} else {
			PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		}
		return NULL;
	}

	Py_RETURN_NONE;

}


PyObject* parse (
	PyObject *self,
	PyObject *args
) {

	char *name = NULL;
	if (!PyArg_ParseTuple(args, "s", &name)) {
		return NULL;
	}

	return parse_(name);

}