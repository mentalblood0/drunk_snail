#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

%%{
	machine test;
	write data;
}%%



int test(char* input)
{
	const char *p = input;
	const char *pe = input + strlen(input);
	const char *eof = pe;
	const char* ts, * te;
	int cs, act, top, stack[2], curline;

	%%{
	
		action action_start_line {
			printf("start_line\n");
		}
		action action_end_line {
			printf("end_line\n");
		}
		action action_empty_line {
			printf("empty_line %d='%c'\n", p - input, *p);
		}

		action action_param {
			printf("param\n");
		}
		action action_ref {
			printf("ref\n");
		}

		action action_other_left {
			printf("other_left\n");
		}
		action action_other_right {
			printf("other_right\n");
		}
		action action_name_start {
			printf("name_start %d\n", p - input);
		}
		action action_name_end {
			printf("name_end %d\n", p - input);
		}

		action action_start_expression {
			printf("start_expression %d\n", p - input);
		}
		action action_end_expression {
			printf("end_expression %d\n", p - input);
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