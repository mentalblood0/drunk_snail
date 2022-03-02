#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

%%{
	machine compile;
	write data;
}%%



compileComprehension__def {%
J='\n'.join
def render($TEMPLATE_NAME$):
	return J([
%}

compileComprehension__end {%
])
%}

compileComprehension__for {%
for $ARG$ in(($TEMPLATE_NAME$['$ARG$']if list==type($TEMPLATE_NAME$['$ARG$'])else[$TEMPLATE_NAME$['$ARG$']])if'$ARG$'in $TEMPLATE_NAME$ else[$optional?:''$])
%}


compileComprehension__empty {%
"$LINE$",
%}

compileComprehension__param {%
*[f"$OTHER_LEFT${$ARG$}$OTHER_RIGHT$"$compileComprehension__for$],
%}

compileComprehension__ref_before {%
*["$OTHER_LEFT$"+"$OTHER_RIGHT$\n$OTHER_LEFT$".join([
%}

compileComprehension__ref_after {%
])+"$OTHER_RIGHT$"$compileComprehension__for$],
%}


enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};


#define reset_line_properties() {\
	start_line = NULL;\
	end_line = NULL;\
	start_expression = NULL;\
	end_expression = NULL;\
	name_start = NULL;\
	name_end = NULL;\
	action_type = ACTION_NONE;\
	optional = false;\
}


void compileComprehension_(
	CompilationResult *compilation_result,
	char *template_name,
	int template_name_length,
	char **output_end,
	int depth,
	int buffer_size
)
{

	Template *template = dictionaryLookupUnterminated(_templates, template_name, template_name_length);
	if (template == NULL) {
		compilation_result->code = 1;
		compilation_result->message = malloc(sizeof(char) * 128);
		snprintf(
			compilation_result->message, 
			128, 
			"Can not compile template \"%.*s\": not loaded\n", 
			template_name_length, template_name
		);
		return;
	}

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	int cs;

	enum ActionType action_type = ACTION_NONE;
	bool optional = false;

	char *start_line, *end_line, *start_expression, *end_expression, *name_start, *name_end;
	reset_line_properties();

	if (!depth) {
		clearRefs(template);
		compileComprehension__def(output_end, template_name, template_name_length);
	}

	%%{
	
		action action_start_line { start_line = p; }
		action action_end_line {

			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
					compileComprehension__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						template_name, template_name_length
					);
				}
				else if (action_type == ACTION_REF) {
					if (!depth)
						addRef(template, name_start, name_end - name_start);
					compileComprehension__ref_before(output_end, start_line, start_expression - start_line, end_expression, end_line - end_expression);
					compileComprehension_(
						compilation_result,
						name_start,
						name_end - name_start,
						output_end,
						1,
						buffer_size
					);
					if (compilation_result->code == 2) {
						if (!depth) {
							free(compilation_result->result);
							compilation_result->result = NULL;
						}
						return;
					}
					compileComprehension__ref_after(output_end, end_expression, end_line - end_expression, name_start, name_end - name_start, template_name, template_name_length);
				}
			}
			if (action_type == ACTION_NONE)
				compileComprehension__empty(output_end, start_line, end_line - start_line);

			reset_line_properties();

		}

		action action_param { action_type = ACTION_PARAM; }
		action action_ref { action_type = ACTION_REF; }
		action action_optional { optional = true; }

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

		delimeter = '\n';
		other = (any - delimeter)+;

		operator = param | ref | optional;
		name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_name_start %action_name_end;

		expression = (open ' '* operator+ name ' '* close) >action_start_expression %action_end_expression;

		line = (other? expression? other?) >action_start_line %action_end_line;

		template = (line delimeter)* (line - zlen)?;
		main := template;

		write init;
		write exec;
	}%%

	if (!depth) {
		compileComprehension__end(output_end);
		**output_end = 0;
	}
};


static PyObject *compileComprehension (
	PyObject *self,
	PyObject *args
) {

	char *name;
	int buffer_size;
	
	if (!PyArg_ParseTuple(args, "si", &name, &buffer_size)) {
		return PyLong_FromLong(-1);
	}

	CompilationResult compilation_result;
	compilation_result.code = 0;
	compilation_result.message = NULL;

	compilation_result.result = malloc(sizeof(char) * buffer_size);
	char *_output_end = compilation_result.result;

	compileComprehension_(
		&compilation_result,
		name,
		strlen(name),
		&_output_end,
		0,
		buffer_size
	);

	PyObject *t = PyTuple_New(3);
	PyTuple_SetItem(t, 0, PyLong_FromLong(compilation_result.code));
	PyTuple_SetItem(t, 1, PyUnicode_FromString(compilation_result.message ? compilation_result.message : ""));
	PyTuple_SetItem(t, 2, PyUnicode_FromString(compilation_result.result ? compilation_result.result : ""));
	return t;

}