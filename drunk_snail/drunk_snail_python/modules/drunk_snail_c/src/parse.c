
/* #line 1 "parse.rl" */
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

#include "../include/parse.h"




/* #line 25 "parse.c" */
static const int parse_python_start = 0;
static const int parse_python_first_final = 0;
static const int parse_python_error = -1;

static const int parse_python_en_main = 0;


/* #line 24 "parse.rl" */




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

	
/* #line 103 "parse.c" */
	{
	cs = parse_python_start;
	}

/* #line 108 "parse.c" */
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr1:
/* #line 94 "parse.rl" */
	{ line->tokens.line.start = p; }
/* #line 95 "parse.rl" */
	{

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
	goto st0;
tr4:
/* #line 95 "parse.rl" */
	{

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
	goto st0;
tr37:
/* #line 129 "parse.rl" */
	{ line->tokens.expression.end = p; }
/* #line 130 "parse.rl" */
	{ line->has_expressions = true; }
/* #line 95 "parse.rl" */
	{

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
	goto st0;
tr40:
/* #line 130 "parse.rl" */
	{ line->has_expressions = true; }
/* #line 95 "parse.rl" */
	{

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
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
/* #line 222 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr1;
		case 60: goto tr2;
	}
	goto tr0;
tr0:
/* #line 94 "parse.rl" */
	{ line->tokens.line.start = p; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
/* #line 236 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
	}
	goto st1;
tr2:
/* #line 94 "parse.rl" */
	{ line->tokens.line.start = p; }
/* #line 125 "parse.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
	goto st2;
tr5:
/* #line 125 "parse.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
/* #line 262 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 33: goto st3;
		case 60: goto tr5;
	}
	goto st1;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st4;
		case 60: goto tr5;
	}
	goto st1;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st5;
		case 60: goto tr5;
	}
	goto st1;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st5;
		case 40: goto st6;
		case 60: goto tr5;
	}
	goto st1;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st7;
		case 112: goto st17;
		case 114: goto st70;
		case 115: goto st78;
	}
	goto st1;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 112: goto st8;
	}
	goto st1;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st9;
	}
	goto st1;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st10;
	}
	goto st1;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st11;
	}
	goto st1;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 110: goto st12;
	}
	goto st1;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st13;
	}
	goto st1;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 108: goto st14;
	}
	goto st1;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st15;
		case 60: goto tr5;
	}
	goto st1;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr22;
		case 60: goto tr5;
	}
	goto st1;
tr22:
/* #line 119 "parse.rl" */
	{ line->flags.optional = true; }
	goto st16;
tr106:
/* #line 120 "parse.rl" */
	{ line->flags.strict = true; }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
/* #line 415 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 112: goto st17;
		case 114: goto st70;
	}
	goto st1;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st18;
	}
	goto st1;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st19;
	}
	goto st1;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st20;
	}
	goto st1;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 109: goto st21;
	}
	goto st1;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st22;
		case 60: goto tr5;
	}
	goto st1;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 95: goto tr28;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr28;
	} else if ( (*p) >= 65 )
		goto tr28;
	goto st1;
tr28:
/* #line 117 "parse.rl" */
	{ line->action = ACTION_PARAM; }
/* #line 122 "parse.rl" */
	{ line->tokens.name.start = p; }
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
/* #line 498 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto tr29;
		case 45: goto tr30;
		case 60: goto tr5;
		case 95: goto st23;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st23;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st23;
	} else
		goto st23;
	goto st1;
tr29:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
/* #line 523 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st24;
		case 45: goto st25;
		case 60: goto tr5;
	}
	goto st1;
tr30:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
/* #line 539 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st26;
		case 60: goto tr5;
	}
	goto st1;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 62: goto st27;
	}
	goto st1;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 10: goto tr37;
		case 60: goto tr38;
	}
	goto tr36;
tr36:
/* #line 129 "parse.rl" */
	{ line->tokens.expression.end = p; }
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
/* #line 573 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
	}
	goto st28;
tr41:
/* #line 125 "parse.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
	goto st29;
tr38:
/* #line 129 "parse.rl" */
	{ line->tokens.expression.end = p; }
/* #line 125 "parse.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
	goto st29;
tr82:
/* #line 125 "parse.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
/* #line 129 "parse.rl" */
	{ line->tokens.expression.end = p; }
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
/* #line 608 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 33: goto st30;
		case 60: goto tr41;
	}
	goto st28;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 10: goto tr40;
		case 45: goto st31;
		case 60: goto tr41;
	}
	goto st28;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 10: goto tr40;
		case 45: goto st32;
		case 60: goto tr41;
	}
	goto st28;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 10: goto tr40;
		case 32: goto st32;
		case 40: goto st33;
		case 60: goto tr41;
	}
	goto st28;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 111: goto st34;
		case 112: goto st44;
		case 114: goto st54;
		case 115: goto st63;
	}
	goto st28;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 112: goto st35;
	}
	goto st28;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 116: goto st36;
	}
	goto st28;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 105: goto st37;
	}
	goto st28;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 111: goto st38;
	}
	goto st28;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 110: goto st39;
	}
	goto st28;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 97: goto st40;
	}
	goto st28;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 108: goto st41;
	}
	goto st28;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 10: goto tr40;
		case 41: goto st42;
		case 60: goto tr41;
	}
	goto st28;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 10: goto tr40;
		case 40: goto tr58;
		case 60: goto tr41;
	}
	goto st28;
tr58:
/* #line 119 "parse.rl" */
	{ line->flags.optional = true; }
	goto st43;
tr89:
/* #line 120 "parse.rl" */
	{ line->flags.strict = true; }
	goto st43;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
/* #line 761 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 112: goto st44;
		case 114: goto st54;
	}
	goto st28;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 97: goto st45;
	}
	goto st28;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 114: goto st46;
	}
	goto st28;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 97: goto st47;
	}
	goto st28;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 109: goto st48;
	}
	goto st28;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 10: goto tr40;
		case 41: goto st49;
		case 60: goto tr41;
	}
	goto st28;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 95: goto tr64;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr64;
	} else if ( (*p) >= 65 )
		goto tr64;
	goto st28;
tr64:
/* #line 117 "parse.rl" */
	{ line->action = ACTION_PARAM; }
/* #line 122 "parse.rl" */
	{ line->tokens.name.start = p; }
	goto st50;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
/* #line 844 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 32: goto tr65;
		case 45: goto tr66;
		case 60: goto tr41;
		case 95: goto st50;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st50;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st50;
	} else
		goto st50;
	goto st28;
tr65:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st51;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
/* #line 869 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 32: goto st51;
		case 45: goto st52;
		case 60: goto tr41;
	}
	goto st28;
tr66:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st52;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
/* #line 885 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 45: goto st53;
		case 60: goto tr41;
	}
	goto st28;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 62: goto st27;
	}
	goto st28;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 101: goto st55;
	}
	goto st28;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 102: goto st56;
	}
	goto st28;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 10: goto tr40;
		case 41: goto st57;
		case 60: goto tr41;
	}
	goto st28;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 95: goto tr74;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr74;
	} else if ( (*p) >= 65 )
		goto tr74;
	goto st28;
tr74:
/* #line 118 "parse.rl" */
	{ line->action = ACTION_REF; }
/* #line 122 "parse.rl" */
	{ line->tokens.name.start = p; }
	goto st58;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
/* #line 957 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 32: goto tr75;
		case 45: goto tr76;
		case 60: goto tr41;
		case 95: goto st58;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st58;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st58;
	} else
		goto st58;
	goto st28;
tr75:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st59;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
/* #line 982 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 32: goto st59;
		case 45: goto st60;
		case 60: goto tr41;
	}
	goto st28;
tr76:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st60;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
/* #line 998 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr40;
		case 45: goto st61;
		case 60: goto tr41;
	}
	goto st28;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 62: goto st62;
	}
	goto st28;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 10: goto tr37;
		case 60: goto tr82;
	}
	goto tr36;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 116: goto st64;
	}
	goto st28;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 114: goto st65;
	}
	goto st28;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 105: goto st66;
	}
	goto st28;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 99: goto st67;
	}
	goto st28;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 10: goto tr40;
		case 60: goto tr41;
		case 116: goto st68;
	}
	goto st28;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 10: goto tr40;
		case 41: goto st69;
		case 60: goto tr41;
	}
	goto st28;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 10: goto tr40;
		case 40: goto tr89;
		case 60: goto tr41;
	}
	goto st28;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 101: goto st71;
	}
	goto st1;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 102: goto st72;
	}
	goto st1;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st73;
		case 60: goto tr5;
	}
	goto st1;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 95: goto tr93;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr93;
	} else if ( (*p) >= 65 )
		goto tr93;
	goto st1;
tr93:
/* #line 118 "parse.rl" */
	{ line->action = ACTION_REF; }
/* #line 122 "parse.rl" */
	{ line->tokens.name.start = p; }
	goto st74;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
/* #line 1149 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto tr94;
		case 45: goto tr95;
		case 60: goto tr5;
		case 95: goto st74;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st74;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st74;
	} else
		goto st74;
	goto st1;
tr94:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st75;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
/* #line 1174 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st75;
		case 45: goto st76;
		case 60: goto tr5;
	}
	goto st1;
tr95:
/* #line 123 "parse.rl" */
	{ line->tokens.name.end = p; }
	goto st76;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
/* #line 1190 "parse.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st77;
		case 60: goto tr5;
	}
	goto st1;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 62: goto st62;
	}
	goto st1;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st79;
	}
	goto st1;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st80;
	}
	goto st1;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st81;
	}
	goto st1;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 99: goto st82;
	}
	goto st1;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st83;
	}
	goto st1;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st84;
		case 60: goto tr5;
	}
	goto st1;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr106;
		case 60: goto tr5;
	}
	goto st1;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
	case 8: 
	case 9: 
	case 10: 
	case 11: 
	case 12: 
	case 13: 
	case 14: 
	case 15: 
	case 16: 
	case 17: 
	case 18: 
	case 19: 
	case 20: 
	case 21: 
	case 22: 
	case 23: 
	case 24: 
	case 25: 
	case 26: 
	case 70: 
	case 71: 
	case 72: 
	case 73: 
	case 74: 
	case 75: 
	case 76: 
	case 77: 
	case 78: 
	case 79: 
	case 80: 
	case 81: 
	case 82: 
	case 83: 
	case 84: 
/* #line 95 "parse.rl" */
	{

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
	break;
	case 28: 
	case 29: 
	case 30: 
	case 31: 
	case 32: 
	case 33: 
	case 34: 
	case 35: 
	case 36: 
	case 37: 
	case 38: 
	case 39: 
	case 40: 
	case 41: 
	case 42: 
	case 43: 
	case 44: 
	case 45: 
	case 46: 
	case 47: 
	case 48: 
	case 49: 
	case 50: 
	case 51: 
	case 52: 
	case 53: 
	case 54: 
	case 55: 
	case 56: 
	case 57: 
	case 58: 
	case 59: 
	case 60: 
	case 61: 
	case 63: 
	case 64: 
	case 65: 
	case 66: 
	case 67: 
	case 68: 
	case 69: 
/* #line 130 "parse.rl" */
	{ line->has_expressions = true; }
/* #line 95 "parse.rl" */
	{

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
	break;
	case 27: 
	case 62: 
/* #line 129 "parse.rl" */
	{ line->tokens.expression.end = p; }
/* #line 130 "parse.rl" */
	{ line->has_expressions = true; }
/* #line 95 "parse.rl" */
	{

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
	break;
/* #line 1527 "parse.c" */
	}
	}

	}

/* #line 161 "parse.rl" */


	template->lines.length -= 1;

};


parse_result parse(char *name) {

	parse_result result;
	result.code = 0;
	result.message = NULL;

	_parse(name, strlen(name), 0, &result);

	return result;

}