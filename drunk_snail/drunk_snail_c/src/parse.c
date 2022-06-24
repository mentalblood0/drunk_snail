
/* #line 1 "compileComprehension_preprocessed.rl" */
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




/* #line 24 "compileComprehension.c" */
static const int parse_start = 0;
static const int parse_first_final = 0;
static const int parse_error = -1;

static const int parse_en_main = 0;


/* #line 23 "compileComprehension_preprocessed.rl" */




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

	char *value;
	Py_ssize_t j;
	Py_ssize_t list_size;
	Py_ssize_t value_size;
	PyObject *param_values;
	PyObject *ref_values;
	PyObject *item;

	Line *line = NULL;

	size_t i;
	bool alloc_error = false;

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	size_t cs;

	drunk_malloc_one_parse_(line, sizeof(Line));
	initLine(*line);

	
/* #line 103 "compileComprehension.c" */
	{
	cs = parse_start;
	}

/* #line 108 "compileComprehension.c" */
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr1:
/* #line 94 "compileComprehension_preprocessed.rl" */
	{ line->tokens.line.start = p; }
/* #line 95 "compileComprehension_preprocessed.rl" */
	{

			line->tokens.line.end = p;
			listPush(template->lines, line, alloc_error);
			if (alloc_error) {
				free(line);
				exit_parse_();
			}

			verifyAction(*line);

			if (line->action != ACTION_NONE) {
				drunk_malloc_one_parse_(line->tokens.name.copy, sizeof(char) * (line->tokens.name.end - line->tokens.name.start + 1));
				memcpy(line->tokens.name.copy, line->tokens.name.start, line->tokens.name.end - line->tokens.name.start);
				line->tokens.name.copy[line->tokens.name.end - line->tokens.name.start] = 0;
			}

			drunk_malloc_one_parse_(line, sizeof(Line));
			initLine(*line)

		}
	goto st0;
tr4:
/* #line 95 "compileComprehension_preprocessed.rl" */
	{

			line->tokens.line.end = p;
			listPush(template->lines, line, alloc_error);
			if (alloc_error) {
				free(line);
				exit_parse_();
			}

			verifyAction(*line);

			if (line->action != ACTION_NONE) {
				drunk_malloc_one_parse_(line->tokens.name.copy, sizeof(char) * (line->tokens.name.end - line->tokens.name.start + 1));
				memcpy(line->tokens.name.copy, line->tokens.name.start, line->tokens.name.end - line->tokens.name.start);
				line->tokens.name.copy[line->tokens.name.end - line->tokens.name.start] = 0;
			}

			drunk_malloc_one_parse_(line, sizeof(Line));
			initLine(*line)

		}
	goto st0;
tr50:
/* #line 129 "compileComprehension_preprocessed.rl" */
	{ line->tokens.expression.end = p; }
/* #line 95 "compileComprehension_preprocessed.rl" */
	{

			line->tokens.line.end = p;
			listPush(template->lines, line, alloc_error);
			if (alloc_error) {
				free(line);
				exit_parse_();
			}

			verifyAction(*line);

			if (line->action != ACTION_NONE) {
				drunk_malloc_one_parse_(line->tokens.name.copy, sizeof(char) * (line->tokens.name.end - line->tokens.name.start + 1));
				memcpy(line->tokens.name.copy, line->tokens.name.start, line->tokens.name.end - line->tokens.name.start);
				line->tokens.name.copy[line->tokens.name.end - line->tokens.name.start] = 0;
			}

			drunk_malloc_one_parse_(line, sizeof(Line));
			initLine(*line)

		}
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
/* #line 194 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr1;
		case 60: goto tr2;
	}
	goto tr0;
tr0:
/* #line 94 "compileComprehension_preprocessed.rl" */
	{ line->tokens.line.start = p; }
	goto st1;
tr49:
/* #line 129 "compileComprehension_preprocessed.rl" */
	{ line->tokens.expression.end = p; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
/* #line 212 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
	}
	goto st1;
tr2:
/* #line 94 "compileComprehension_preprocessed.rl" */
	{ line->tokens.line.start = p; }
/* #line 125 "compileComprehension_preprocessed.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
	goto st2;
tr5:
/* #line 125 "compileComprehension_preprocessed.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
	goto st2;
tr51:
/* #line 125 "compileComprehension_preprocessed.rl" */
	{
			if (!(line->tokens.expression.start && line->tokens.name.end))
				line->tokens.expression.start = p;
		}
/* #line 129 "compileComprehension_preprocessed.rl" */
	{ line->tokens.expression.end = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
/* #line 247 "compileComprehension.c" */
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
tr22:
/* #line 119 "compileComprehension_preprocessed.rl" */
	{ line->flags.optional = true; }
	goto st6;
tr71:
/* #line 120 "compileComprehension_preprocessed.rl" */
	{ line->flags.strict = true; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
/* #line 297 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st7;
		case 112: goto st16;
		case 114: goto st44;
		case 115: goto st48;
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
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st17;
	}
	goto st1;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st18;
	}
	goto st1;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st19;
	}
	goto st1;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 109: goto st20;
	}
	goto st1;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st21;
		case 60: goto tr5;
	}
	goto st1;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr28;
		case 60: goto tr5;
		case 95: goto tr29;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr29;
	} else if ( (*p) >= 65 )
		goto tr29;
	goto st1;
tr40:
/* #line 119 "compileComprehension_preprocessed.rl" */
	{ line->flags.optional = true; }
	goto st22;
tr28:
/* #line 117 "compileComprehension_preprocessed.rl" */
	{ line->action = ACTION_PARAM; }
	goto st22;
tr58:
/* #line 120 "compileComprehension_preprocessed.rl" */
	{ line->flags.strict = true; }
	goto st22;
tr63:
/* #line 118 "compileComprehension_preprocessed.rl" */
	{ line->action = ACTION_REF; }
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
/* #line 483 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st23;
		case 115: goto st37;
	}
	goto st1;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 112: goto st24;
	}
	goto st1;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st25;
	}
	goto st1;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st26;
	}
	goto st1;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st27;
	}
	goto st1;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 110: goto st28;
	}
	goto st1;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st29;
	}
	goto st1;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 108: goto st30;
	}
	goto st1;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st31;
		case 60: goto tr5;
	}
	goto st1;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr40;
		case 60: goto tr5;
		case 95: goto tr41;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr41;
	} else if ( (*p) >= 65 )
		goto tr41;
	goto st1;
tr29:
/* #line 117 "compileComprehension_preprocessed.rl" */
	{ line->action = ACTION_PARAM; }
/* #line 122 "compileComprehension_preprocessed.rl" */
	{ line->tokens.name.start = p; }
	goto st32;
tr41:
/* #line 119 "compileComprehension_preprocessed.rl" */
	{ line->flags.optional = true; }
/* #line 122 "compileComprehension_preprocessed.rl" */
	{ line->tokens.name.start = p; }
	goto st32;
tr59:
/* #line 120 "compileComprehension_preprocessed.rl" */
	{ line->flags.strict = true; }
/* #line 122 "compileComprehension_preprocessed.rl" */
	{ line->tokens.name.start = p; }
	goto st32;
tr64:
/* #line 118 "compileComprehension_preprocessed.rl" */
	{ line->action = ACTION_REF; }
/* #line 122 "compileComprehension_preprocessed.rl" */
	{ line->tokens.name.start = p; }
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
/* #line 615 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto tr42;
		case 45: goto tr43;
		case 60: goto tr5;
		case 95: goto st32;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st32;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st32;
	} else
		goto st32;
	goto st1;
tr42:
/* #line 123 "compileComprehension_preprocessed.rl" */
	{ line->tokens.name.end = p; }
	goto st33;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
/* #line 640 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st33;
		case 45: goto st34;
		case 60: goto tr5;
	}
	goto st1;
tr43:
/* #line 123 "compileComprehension_preprocessed.rl" */
	{ line->tokens.name.end = p; }
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
/* #line 656 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st35;
		case 60: goto tr5;
	}
	goto st1;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 62: goto st36;
	}
	goto st1;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 10: goto tr50;
		case 60: goto tr51;
	}
	goto tr49;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st38;
	}
	goto st1;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st39;
	}
	goto st1;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st40;
	}
	goto st1;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 99: goto st41;
	}
	goto st1;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st42;
	}
	goto st1;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st43;
		case 60: goto tr5;
	}
	goto st1;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr58;
		case 60: goto tr5;
		case 95: goto tr59;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr59;
	} else if ( (*p) >= 65 )
		goto tr59;
	goto st1;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 101: goto st45;
	}
	goto st1;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 102: goto st46;
	}
	goto st1;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st47;
		case 60: goto tr5;
	}
	goto st1;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr63;
		case 60: goto tr5;
		case 95: goto tr64;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr64;
	} else if ( (*p) >= 65 )
		goto tr64;
	goto st1;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st49;
	}
	goto st1;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st50;
	}
	goto st1;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st51;
	}
	goto st1;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 99: goto st52;
	}
	goto st1;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st53;
	}
	goto st1;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st54;
		case 60: goto tr5;
	}
	goto st1;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr71;
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
	case 27: 
	case 28: 
	case 29: 
	case 30: 
	case 31: 
	case 32: 
	case 33: 
	case 34: 
	case 35: 
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
/* #line 95 "compileComprehension_preprocessed.rl" */
	{

			line->tokens.line.end = p;
			listPush(template->lines, line, alloc_error);
			if (alloc_error) {
				free(line);
				exit_parse_();
			}

			verifyAction(*line);

			if (line->action != ACTION_NONE) {
				drunk_malloc_one_parse_(line->tokens.name.copy, sizeof(char) * (line->tokens.name.end - line->tokens.name.start + 1));
				memcpy(line->tokens.name.copy, line->tokens.name.start, line->tokens.name.end - line->tokens.name.start);
				line->tokens.name.copy[line->tokens.name.end - line->tokens.name.start] = 0;
			}

			drunk_malloc_one_parse_(line, sizeof(Line));
			initLine(*line)

		}
	break;
	case 36: 
/* #line 129 "compileComprehension_preprocessed.rl" */
	{ line->tokens.expression.end = p; }
/* #line 95 "compileComprehension_preprocessed.rl" */
	{

			line->tokens.line.end = p;
			listPush(template->lines, line, alloc_error);
			if (alloc_error) {
				free(line);
				exit_parse_();
			}

			verifyAction(*line);

			if (line->action != ACTION_NONE) {
				drunk_malloc_one_parse_(line->tokens.name.copy, sizeof(char) * (line->tokens.name.end - line->tokens.name.start + 1));
				memcpy(line->tokens.name.copy, line->tokens.name.start, line->tokens.name.end - line->tokens.name.start);
				line->tokens.name.copy[line->tokens.name.end - line->tokens.name.start] = 0;
			}

			drunk_malloc_one_parse_(line, sizeof(Line));
			initLine(*line)

		}
	break;
/* #line 1037 "compileComprehension.c" */
	}
	}

	}

/* #line 158 "compileComprehension_preprocessed.rl" */


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