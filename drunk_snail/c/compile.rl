#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

%%{
	machine compile;
	write data;
}%%



compile__def {%
J='\n'.join
def render(<TEMPLATE_NAME>):
	return J([
%}

compile__end {%
])
%}

compile__for {%
for <ARG> in((<TEMPLATE_NAME>['<ARG>']if list==type(<TEMPLATE_NAME>['<ARG>'])else[<TEMPLATE_NAME>['<ARG>']])if'<ARG>'in <TEMPLATE_NAME> else[<optional?:''>])
%}

compile__for_strict {%
for <ARG> in <TEMPLATE_NAME>['<ARG>']
%}


compile__empty {%
"<other[:depth].left+><LINE><other[:depth].right->",
%}

compile__param {%
*[f"<other[:depth].left+><OTHER_LEFT>{<ARG>}<OTHER_RIGHT><other[:depth].right->"<*(strict?compile__for_strict:compile__for)>],
%}

compile__ref_before {%
*[J([
%}

compile__ref_after {%
])<*(strict?compile__for_strict:compile__for)>],
%}


typedef struct Substring {
	char *start;
	int length;
} Substring;


typedef struct Other {
	Substring left;
	Substring right;
} Other;


enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};


typedef struct CompilationResult {
	char *message;
	char *result;
} CompilationResult;


#define reset_line_properties() {\
	start_line = NULL;\
	end_line = NULL;\
	start_expression = NULL;\
	end_expression = NULL;\
	name_start = NULL;\
	name_end = NULL;\
	action_type = ACTION_NONE;\
	optional = false;\
	strict = false;\
}


void compile_(
	CompilationResult *compilation_result,
	char *template_name,
	int template_name_length,
	char **output_end,
	int depth,
	int *buffer_size,
	Other *other,
	int *other_size
)
{

	Template *template = dictionaryLookupUnterminated(_templates, template_name, template_name_length);
	if (template == NULL) {
		compilation_result->message = malloc(sizeof(char) * (template_name_length + 1));
		memcpy(compilation_result->message, template_name, template_name_length);
		compilation_result->message[template_name_length] = 0;
		return;
	}

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	int cs;
	char *new_result;

	enum ActionType action_type = ACTION_NONE;
	bool optional = false;
	bool strict = false;

	char *start_line, *end_line, *start_expression, *end_expression, *name_start, *name_end;
	reset_line_properties();

	if (!depth) {
		clearRefs(template);
		compile__def(output_end, template_name, template_name_length);
	}

	%%{
	
		action action_start_line { start_line = p; }
		action action_end_line {

			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
					compile__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						template_name, template_name_length
					);
				}
				else if (action_type == ACTION_REF) {
					if (depth >= *other_size) {
						*other_size *= 2;
						other = realloc(other, sizeof(other) * (*other_size));
					}
					other[depth].left.start = start_line;
					other[depth].left.length = start_expression - start_line;
					other[depth].right.start = end_expression;
					other[depth].right.length = end_line - end_expression;
					if (!depth)
						addRef(template, name_start, name_end - name_start);
					compile__ref_before(output_end);
					compile_(
						compilation_result,
						name_start,
						name_end - name_start,
						output_end,
						depth + 1,
						buffer_size,
						other,
						other_size
					);
					if (compilation_result->message)
						return;
					compile__ref_after(output_end, name_start, name_end - name_start, template_name, template_name_length);
				}
			}
			if (action_type == ACTION_NONE)
				compile__empty(output_end, start_line, end_line - start_line);

			reset_line_properties();

		}

		action action_param { action_type = ACTION_PARAM; }
		action action_ref { action_type = ACTION_REF; }
		action action_optional { optional = true; }
		action action_strict { strict = true; }

		action action_name_start { name_start = p; }
		action action_name_end { name_end = p; }

		action action_start_expression {
			if (!(start_expression && name_end))
				start_expression = p;
		}
		action action_end_expression { end_expression = p; }

		open = '<!--';
		close = '-->';
		param = '(param)' %action_param;
		ref = '(ref)' %action_ref;
		optional = '(optional)' %action_optional;
		strict = '(strict)' %action_strict;

		delimeter = '\n';
		other = (any - delimeter)+;

		operator = param | ref | optional | strict;
		name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_name_start %action_name_end;

		expression = (open ' '* operator+ name ' '* close) >action_start_expression %action_end_expression;

		line = (other? expression? other?) >action_start_line %action_end_line;

		template = (line delimeter)* (line - zlen)?;
		main := template;

		write init;
		write exec;
	}%%

	if (!depth) {
		compile__end(output_end);
		**output_end = 0;
	}
};


static PyObject *compile (
	PyObject *self,
	PyObject *args
) {

	char *name;
	int buffer_size;
	
	if (!PyArg_ParseTuple(args, "si", &name, &buffer_size))
		return NULL;

	CompilationResult compilation_result;
	compilation_result.message = NULL;
	compilation_result.result = malloc(sizeof(char) * buffer_size);

	int other_size = 16;
	Other *other = malloc(sizeof(Other) * other_size);

	char *_output_end = compilation_result.result;

	compile_(
		&compilation_result,
		name,
		strlen(name),
		&_output_end,
		0,
		&buffer_size,
		other,
		&other_size
	);

	if (compilation_result.message) {
		PyErr_SetString(PyExc_KeyError, compilation_result.message);
		return NULL;
	}

	PyObject *t = PyTuple_New(2);
	PyTuple_SetItem(t, 0, PyUnicode_FromString(compilation_result.result));
	PyTuple_SetItem(t, 1, PyLong_FromLong(buffer_size));
	return t;

}