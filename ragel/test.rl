#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

%%{
	machine test;
	write data;
}%%



enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};


int test(char* input)
{
	char *p = input;
	const char *pe = input + strlen(input);
	const char *eof = pe;
	const char* ts, * te;
	int cs, act, top, stack[2], curline;

	enum ActionType action_type = ACTION_NONE;

	char *start_line, *end_line, *start_expression, *end_expression, *name_start, *name_end;

	%%{
	
		action action_start_line {

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;
			action_type = ACTION_NONE;

			printf("start_line %ld\n", p - input);
			start_line = p;
		}
		action action_end_line {
			printf("end_line %ld\n", p - input);
			end_line = p;

			if (action_type == ACTION_PARAM)
				printf(
					"---------- PARAM ----------\n"
					"other_left: '%.*s'\n"
					"name: '%.*s'\n"
					"other_right: '%.*s'\n"
					"---------------------------\n",
					start_expression - start_line, start_line,
					name_end - name_start, name_start,
					end_line - end_expression, end_expression
				);
			else if (action_type == ACTION_REF)
				printf(
					"----------- REF -----------\n"
					"other_left: '%.*s'\n"
					"name: '%.*s'\n"
					"other_right: '%.*s'\n"
					"---------------------------\n",
					start_expression - start_line, start_line,
					name_end - name_start, name_start,
					end_line - end_expression, end_expression
				);
			else if (action_type == ACTION_NONE)
				printf(
					"---------- EMPTY ----------\n"
					"line: '%.*s'\n"
					"---------------------------\n",
					end_line - start_line, start_line
				);

		}

		action action_param {
			action_type = ACTION_PARAM;
			printf("param\n");
		}
		action action_ref {
			action_type = ACTION_REF;
			printf("ref\n");
		}

		action action_name_start {
			printf("name_start %ld\n", p - input);
			name_start = p;
		}
		action action_name_end {
			printf("name_end %ld\n", p - input);
			name_end = p;
		}

		action action_start_expression {
			if (!(start_expression && name_end)) {
				printf("start_expression %ld\n", p - input);
				start_expression = p;
			}
		}
		action action_end_expression {
			printf("end_expression %ld\n", p - input);
			end_expression = p;
		}

		open = '<!--';
		close = '-->';
		param = '(param)' %action_param;
		ref = '(ref)' %action_ref;

		delimeter = '\n';
		other = (any - delimeter)+;

		operator = param | ref;
		name = (alpha+ alnum*) >action_name_start %action_name_end;

		expression = (open ' '* operator+ name ' '* close) >action_start_expression %action_end_expression;

		line = (other? expression? other?) >action_start_line %action_end_line;

		template = (line delimeter)* (line - zlen)?;
		main := template;

		# Initialize and execute.
		write init;
		write exec;
	}%%

	return 0;
};