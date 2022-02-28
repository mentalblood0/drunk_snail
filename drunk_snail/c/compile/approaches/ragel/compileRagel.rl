#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

%%{
	machine compile;
	write data;
}%%



compileRagel__def {%
j=''.join
J='\n'.join
def render($TEMPLATE_NAME$):
	return J([
%}

compileRagel__end {%
])
%}

compileRagel__for {%
for $ARG$ in ([$optional?:None$] if ((not $TEMPLATE_NAME$) or (not '$ARG$' in $TEMPLATE_NAME$)) else ($TEMPLATE_NAME$['$ARG$'] if type($TEMPLATE_NAME$['$ARG$']) == list else [$TEMPLATE_NAME$['$ARG$']]))
%}


compileRagel__empty {%
"$LINE$",
%}

compileRagel__param {%
*[f"$OTHER_LEFT${$ARG$}$OTHER_RIGHT$"$compileRagel__for$],
%}

compileRagel__ref_before {%
*[j(["$OTHER_LEFT$","$OTHER_RIGHT$\n$OTHER_LEFT$".join([
%}

compileRagel__ref_after {%
]),"$OTHER_RIGHT$"])$compileRagel__for$],
%}


enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};


char compileRagel__indent[2] = "\t";

void compileRagel_(
	CompilationResult *compilation_result,
	char *template_name,
	int template_name_length,
	Tree *templates_tree,
	char **output_end,
	int depth,
	int buffer_size
)
{

	Template *template = dictionaryLookupUnterminated(templates_tree, template_name, template_name_length);
	if (template == NULL) {
		compilation_result->code = 1;
		compilation_result->message = malloc(sizeof(char) * 256);
		snprintf(
			compilation_result->message, 
			256, 
			"Can not compile template \"%.*s\": not loaded\n", 
			template_name_length, template_name
		);
		return;
	}
	
	char *input = template->text;

	char *p = input;
	const char *pe = input + template->length;
	const char *eof = pe;
	const char *ts, *te;
	int cs, act, top, stack[2], curline;

	enum ActionType action_type = ACTION_NONE;
	bool optional = false;

	char *start_line, *end_line, *start_expression, *end_expression, *name_start, *name_end;

	if (compilation_result->result == NULL) {
		// printf("malloc\n");
		compilation_result->result = malloc(sizeof(char) * buffer_size);
		output_end = malloc(sizeof(char*) * 1);
		*output_end = compilation_result->result;
	}

	// printf("after init\n");

	if (!depth) {
		compileRagel__def(output_end, template_name, template_name_length);
		// printf("after compileRagel__def\n");
	}

	%%{
	
		action action_start_line {

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;
			action_type = ACTION_NONE;
			optional = false;

			// printf("start_line %ld %ld\n", p - input, (*output_end) - compilation_result->result);
			start_line = p;
		}
		action action_end_line {
			// printf("end_line %ld\n", p - input);
			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
					// printf(
					// 	"---------- PARAM ----------\n"
					// 	"other_left: '%.*s'\n"
					// 	"name: '%.*s'\n"
					// 	"other_right: '%.*s'\n"
					// 	"---------------------------\n",
					// 	start_expression - start_line, start_line,
					// 	name_end - name_start, name_start,
					// 	end_line - end_expression, end_expression
					// );
					compileRagel__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						template_name, template_name_length
					);
					// printf("after compileRagel__param\n");
				}
				else if (action_type == ACTION_REF) {
					// printf(
					// 	"----------- REF -----------\n"
					// 	"other_left: '%.*s'\n"
					// 	"name: '%.*s'\n"
					// 	"other_right: '%.*s'\n"
					// 	"---------------------------\n",
					// 	start_expression - start_line, start_line,
					// 	name_end - name_start, name_start,
					// 	end_line - end_expression, end_expression
					// );
					compileRagel__ref_before(output_end, start_line, start_expression - start_line, end_expression, end_line - end_expression);
					// printf("after compileRagel__ref_before\n");
					compileRagel_(
						compilation_result,
						name_start,
						name_end - name_start,
						templates_tree,
						output_end,
						depth + 1,
						buffer_size
					);
					if (compilation_result->code == 2) {
						if (!depth) {
							free(compilation_result->result);
							compilation_result->result = NULL;
						}
						return;
					}
					compileRagel__ref_after(output_end, end_expression, end_line - end_expression, name_start, name_end - name_start, template_name, template_name_length);
					// printf("after compileRagel__ref_after\n");
				}
			}
			if (action_type == ACTION_NONE) {
				// printf(
				// 	"---------- EMPTY ----------\n"
				// 	"line: '%.*s'\n"
				// 	"---------------------------\n",
				// 	end_line - start_line, start_line
				// );
				compileRagel__empty(output_end, start_line, end_line - start_line);
				// printf("after compileRagel__empty\n");
			}

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;
			action_type = ACTION_NONE;
			optional = false;

		}

		action action_param {
			action_type = ACTION_PARAM;
			// printf("param\n");
		}
		action action_ref {
			action_type = ACTION_REF;
			// printf("ref\n");
		}
		action action_optional {
			optional = true;
			// printf("optional\n");
		}

		action action_name_start {
			// printf("name_start %ld\n", p - input);
			name_start = p;
		}
		action action_name_end {
			// printf("name_end %ld\n", p - input);
			name_end = p;
		}

		action action_start_expression {
			if (!(start_expression && name_end)) {
				// printf("start_expression %ld\n", p - input);
				start_expression = p;
			}
		}
		action action_end_expression {
			// printf("end_expression %ld\n", p - input);
			end_expression = p;
		}

		open = '<!--';
		close = '-->';
		param = '(param)' %action_param;
		ref = '(ref)' %action_ref;
		optional = '(optional)' %action_optional;

		delimeter = '\n';
		other = (any - delimeter)+;

		unknown_operator = '(' [a-zA-Z_][a-zA-Z_0-9]* ')';
		operator = param | ref | optional;
		name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_name_start %action_name_end;

		expression = (open ' '* operator+ name ' '* close) >action_start_expression %action_end_expression;

		line = (other? expression? other?) >action_start_line %action_end_line;

		template = (line delimeter)* (line - zlen)?;
		main := template;

		# Initialize and execute.
		write init;
		write exec;
	}%%

	if (!depth) {
		compileRagel__end(output_end);
		// printf("after compileRagel__end\n");
		**output_end = 0;
	}
};


static PyObject *compileRagel (
	PyObject *self,
	PyObject *args
) {

	char *name;
	int buffer_size;
	
	if (!PyArg_ParseTuple(args, "si", &name, &buffer_size)) {
		return PyLong_FromLong(-1);
	}

	int name_length = 0;
	for (name_length = 0; name[name_length]; name_length++);

	CompilationResult *compilation_result = malloc(sizeof(CompilationResult) * 1);
	compilation_result->code = 0;
	compilation_result->message = NULL;
	compilation_result->result = NULL;
	compileRagel_(
		compilation_result,
		name,
		name_length,
		_templates,
		NULL,
		0,
		buffer_size
	);

	PyObject *t = PyTuple_New(3);
	PyTuple_SetItem(t, 0, PyLong_FromLong(compilation_result->code));
	if (compilation_result->message)
		PyTuple_SetItem(t, 1, PyUnicode_FromString(compilation_result->message));
	else
		PyTuple_SetItem(t, 1, PyUnicode_FromString(""));

	if (compilation_result->result)
		PyTuple_SetItem(t, 2, PyUnicode_FromString(compilation_result->result));
	else
		PyTuple_SetItem(t, 2, PyUnicode_FromString(""));
	
	free(compilation_result);

	return t;

}