
/* #line 1 "compileRagel_preprocessed.rl" */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


/* #line 10 "compileRagel.c" */
static const int compile_start = 0;
static const int compile_first_final = 0;
static const int compile_error = -1;

static const int compile_en_main = 0;


/* #line 9 "compileRagel_preprocessed.rl" */




char *compileRagel__def_strings[2] = {
	"j = '\\n'.join\ndef render(",
	"):\n\treturn j(["
};
#define compileRagel__def(target, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	memcpy(target, compileRagel__def_strings[0], 25); target += 25;\
	memcpy(target, TEMPLATE_NAME, TEMPLATE_NAME_length); target += TEMPLATE_NAME_length;\
	memcpy(target, compileRagel__def_strings[1], 14); target += 14;\
};

char *compileRagel__end_strings[1] = {
	"])"
};
#define compileRagel__end(target) {\
	memcpy(target, compileRagel__end_strings[0], 2); target += 2;\
};

char *compileRagel__for_strings[11] = {
	"for ",
	" in ([None] if ((not ",
	") or (not '",
	"' in ",
	")) else (",
	"['",
	"'] if type(",
	"['",
	"']) == list else [",
	"['",
	"']]))"
};
#define compileRagel__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	memcpy(target, compileRagel__for_strings[0], 4); target += 4;\
	memcpy(target, ARG, ARG_length); target += ARG_length;\
	memcpy(target, compileRagel__for_strings[1], 21); target += 21;\
	memcpy(target, TEMPLATE_NAME, TEMPLATE_NAME_length); target += TEMPLATE_NAME_length;\
	memcpy(target, compileRagel__for_strings[2], 11); target += 11;\
	memcpy(target, ARG, ARG_length); target += ARG_length;\
	memcpy(target, compileRagel__for_strings[3], 5); target += 5;\
	memcpy(target, TEMPLATE_NAME, TEMPLATE_NAME_length); target += TEMPLATE_NAME_length;\
	memcpy(target, compileRagel__for_strings[4], 9); target += 9;\
	memcpy(target, TEMPLATE_NAME, TEMPLATE_NAME_length); target += TEMPLATE_NAME_length;\
	memcpy(target, compileRagel__for_strings[5], 2); target += 2;\
	memcpy(target, ARG, ARG_length); target += ARG_length;\
	memcpy(target, compileRagel__for_strings[6], 11); target += 11;\
	memcpy(target, TEMPLATE_NAME, TEMPLATE_NAME_length); target += TEMPLATE_NAME_length;\
	memcpy(target, compileRagel__for_strings[7], 2); target += 2;\
	memcpy(target, ARG, ARG_length); target += ARG_length;\
	memcpy(target, compileRagel__for_strings[8], 18); target += 18;\
	memcpy(target, TEMPLATE_NAME, TEMPLATE_NAME_length); target += TEMPLATE_NAME_length;\
	memcpy(target, compileRagel__for_strings[9], 2); target += 2;\
	memcpy(target, ARG, ARG_length); target += ARG_length;\
	memcpy(target, compileRagel__for_strings[10], 5); target += 5;\
};


int compileRagel__empty__i;
char *compileRagel__empty_strings[2] = {
	"\"",
	"\","
};
#define compileRagel__empty(target, LINE, LINE_length, INDENT, INDENT_length, INNER_INDENT_SIZE) {\
	memcpy(target, compileRagel__empty_strings[0], 1); target += 1;\
	for (compileRagel__empty__i = 0; compileRagel__empty__i < INNER_INDENT_SIZE; compileRagel__empty__i++) {\
		memcpy(target, INDENT, INDENT_length);\
		target += INDENT_length;\
	}\
	memcpy(target, LINE, LINE_length); target += LINE_length;\
	memcpy(target, compileRagel__empty_strings[1], 2); target += 2;\
};

int compileRagel__param__i;
char *compileRagel__param_strings[5] = {
	"*[f\"",
	"{",
	"}",
	"\"",
	"],"
};
#define compileRagel__param(target, OTHER_LEFT, OTHER_LEFT_length, ARG, ARG_length, OTHER_RIGHT, OTHER_RIGHT_length, INDENT, INDENT_length, INNER_INDENT_SIZE, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	memcpy(target, compileRagel__param_strings[0], 4); target += 4;\
	for (compileRagel__param__i = 0; compileRagel__param__i < INNER_INDENT_SIZE; compileRagel__param__i++) {\
		memcpy(target, INDENT, INDENT_length);\
		target += INDENT_length;\
	}\
	memcpy(target, OTHER_LEFT, OTHER_LEFT_length); target += OTHER_LEFT_length;\
	memcpy(target, compileRagel__param_strings[1], 1); target += 1;\
	memcpy(target, ARG, ARG_length); target += ARG_length;\
	memcpy(target, compileRagel__param_strings[2], 1); target += 1;\
	memcpy(target, OTHER_RIGHT, OTHER_RIGHT_length); target += OTHER_RIGHT_length;\
	memcpy(target, compileRagel__param_strings[3], 1); target += 1;\
	compileRagel__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	memcpy(target, compileRagel__param_strings[4], 2); target += 2;\
};

char *compileRagel__ref_strings[4] = {
	"*[j([",
	"compile(getTemplate(ARG))",
	"])",
	"],"
};
#define compileRagel__ref(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	memcpy(target, compileRagel__ref_strings[0], 5); target += 5;\
	memcpy(target, compileRagel__ref_strings[1], 25); target += 25;\
	memcpy(target, compileRagel__ref_strings[2], 2); target += 2;\
	compileRagel__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	memcpy(target, compileRagel__ref_strings[3], 2); target += 2;\
};


enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};


char compileRagel__indent[2] = "\t";

void compileRagel_(
	CompilationResult *compilation_result,
	char *template_name,
	Tree *templates_tree,
	int inner_indent_size,
	int buffer_size
)
{

	Template *template = dictionaryLookup(templates_tree, template_name);
	if (template == NULL) {
		compilation_result->code = 1;
		compilation_result->message = malloc(sizeof(char) * 256);
		snprintf(
			compilation_result->message, 
			256, 
			"Can not compile template \"%s\": not loaded\n", 
			template_name
		);
		return;
	}
	
	char *input = template->text;

	int template_name_length = 0;
	for (template_name_length = 0; template_name[template_name_length]; template_name_length++);

	char *p = input;
	const char *pe = input + strlen(input);
	const char *eof = pe;
	const char *ts, *te;
	int cs, act, top, stack[2], curline;

	enum ActionType action_type = ACTION_NONE;

	char *start_line, *end_line, *start_expression, *end_expression, *name_start, *name_end;

	if (!compilation_result->result) {
		compilation_result->result = malloc(sizeof(char) * buffer_size);
	}
	char *output_end = compilation_result->result;

	printf("after init\n");

	compileRagel__def(output_end, template_name, template_name_length);
	printf("after compileRagel__def\n");

	
/* #line 189 "compileRagel.c" */
	{
	cs = compile_start;
	}

/* #line 194 "compileRagel.c" */
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr1:
/* #line 180 "compileRagel_preprocessed.rl" */
	{

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
/* #line 193 "compileRagel_preprocessed.rl" */
	{
			printf("end_line %ld\n", p - input);
			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
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
					compileRagel__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						compileRagel__indent, 1, inner_indent_size,
						template_name, template_name_length
					);
					printf("after compileRagel__param\n");
				}
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
			}
			if (action_type == ACTION_NONE) {
				printf(
					"---------- EMPTY ----------\n"
					"line: '%.*s'\n"
					"---------------------------\n",
					end_line - start_line, start_line
				);
				compileRagel__empty(output_end, start_line, end_line - start_line, compileRagel__indent, 1, inner_indent_size);
				printf("after compileRagel__empty\n");
			}

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;

		}
	goto st0;
tr4:
/* #line 193 "compileRagel_preprocessed.rl" */
	{
			printf("end_line %ld\n", p - input);
			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
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
					compileRagel__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						compileRagel__indent, 1, inner_indent_size,
						template_name, template_name_length
					);
					printf("after compileRagel__param\n");
				}
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
			}
			if (action_type == ACTION_NONE) {
				printf(
					"---------- EMPTY ----------\n"
					"line: '%.*s'\n"
					"---------------------------\n",
					end_line - start_line, start_line
				);
				compileRagel__empty(output_end, start_line, end_line - start_line, compileRagel__indent, 1, inner_indent_size);
				printf("after compileRagel__empty\n");
			}

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;

		}
	goto st0;
tr27:
/* #line 275 "compileRagel_preprocessed.rl" */
	{
			printf("end_expression %ld\n", p - input);
			end_expression = p;
		}
/* #line 193 "compileRagel_preprocessed.rl" */
	{
			printf("end_line %ld\n", p - input);
			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
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
					compileRagel__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						compileRagel__indent, 1, inner_indent_size,
						template_name, template_name_length
					);
					printf("after compileRagel__param\n");
				}
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
			}
			if (action_type == ACTION_NONE) {
				printf(
					"---------- EMPTY ----------\n"
					"line: '%.*s'\n"
					"---------------------------\n",
					end_line - start_line, start_line
				);
				compileRagel__empty(output_end, start_line, end_line - start_line, compileRagel__indent, 1, inner_indent_size);
				printf("after compileRagel__empty\n");
			}

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;

		}
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
/* #line 403 "compileRagel.c" */
	switch( (*p) ) {
		case 10: goto tr1;
		case 60: goto tr2;
	}
	goto tr0;
tr0:
/* #line 180 "compileRagel_preprocessed.rl" */
	{

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
	goto st1;
tr26:
/* #line 275 "compileRagel_preprocessed.rl" */
	{
			printf("end_expression %ld\n", p - input);
			end_expression = p;
		}
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
/* #line 436 "compileRagel.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
	}
	goto st1;
tr2:
/* #line 180 "compileRagel_preprocessed.rl" */
	{

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
/* #line 269 "compileRagel_preprocessed.rl" */
	{
			if (!(start_expression && name_end)) {
				printf("start_expression %ld\n", p - input);
				start_expression = p;
			}
		}
	goto st2;
tr5:
/* #line 269 "compileRagel_preprocessed.rl" */
	{
			if (!(start_expression && name_end)) {
				printf("start_expression %ld\n", p - input);
				start_expression = p;
			}
		}
	goto st2;
tr28:
/* #line 269 "compileRagel_preprocessed.rl" */
	{
			if (!(start_expression && name_end)) {
				printf("start_expression %ld\n", p - input);
				start_expression = p;
			}
		}
/* #line 275 "compileRagel_preprocessed.rl" */
	{
			printf("end_expression %ld\n", p - input);
			end_expression = p;
		}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
/* #line 492 "compileRagel.c" */
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
tr17:
/* #line 251 "compileRagel_preprocessed.rl" */
	{
			action_type = ACTION_PARAM;
			printf("param\n");
		}
	goto st6;
tr32:
/* #line 255 "compileRagel_preprocessed.rl" */
	{
			action_type = ACTION_REF;
			printf("ref\n");
		}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
/* #line 548 "compileRagel.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 112: goto st7;
		case 114: goto st18;
	}
	goto st1;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st8;
	}
	goto st1;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st9;
	}
	goto st1;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st10;
	}
	goto st1;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 109: goto st11;
	}
	goto st1;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st12;
		case 60: goto tr5;
	}
	goto st1;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr17;
		case 60: goto tr5;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr18;
	} else if ( (*p) >= 65 )
		goto tr18;
	goto st1;
tr18:
/* #line 251 "compileRagel_preprocessed.rl" */
	{
			action_type = ACTION_PARAM;
			printf("param\n");
		}
/* #line 260 "compileRagel_preprocessed.rl" */
	{
			printf("name_start %ld\n", p - input);
			name_start = p;
		}
	goto st13;
tr33:
/* #line 255 "compileRagel_preprocessed.rl" */
	{
			action_type = ACTION_REF;
			printf("ref\n");
		}
/* #line 260 "compileRagel_preprocessed.rl" */
	{
			printf("name_start %ld\n", p - input);
			name_start = p;
		}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
/* #line 649 "compileRagel.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto tr19;
		case 45: goto tr20;
		case 60: goto tr5;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st13;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st13;
	} else
		goto st13;
	goto st1;
tr19:
/* #line 264 "compileRagel_preprocessed.rl" */
	{
			printf("name_end %ld\n", p - input);
			name_end = p;
		}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
/* #line 676 "compileRagel.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st14;
		case 45: goto st15;
		case 60: goto tr5;
	}
	goto st1;
tr20:
/* #line 264 "compileRagel_preprocessed.rl" */
	{
			printf("name_end %ld\n", p - input);
			name_end = p;
		}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
/* #line 695 "compileRagel.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st16;
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
		case 62: goto st17;
	}
	goto st1;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 10: goto tr27;
		case 60: goto tr28;
	}
	goto tr26;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 101: goto st19;
	}
	goto st1;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 102: goto st20;
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
		case 40: goto tr32;
		case 60: goto tr5;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr33;
	} else if ( (*p) >= 65 )
		goto tr33;
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
	case 18: 
	case 19: 
	case 20: 
	case 21: 
/* #line 193 "compileRagel_preprocessed.rl" */
	{
			printf("end_line %ld\n", p - input);
			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
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
					compileRagel__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						compileRagel__indent, 1, inner_indent_size,
						template_name, template_name_length
					);
					printf("after compileRagel__param\n");
				}
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
			}
			if (action_type == ACTION_NONE) {
				printf(
					"---------- EMPTY ----------\n"
					"line: '%.*s'\n"
					"---------------------------\n",
					end_line - start_line, start_line
				);
				compileRagel__empty(output_end, start_line, end_line - start_line, compileRagel__indent, 1, inner_indent_size);
				printf("after compileRagel__empty\n");
			}

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;

		}
	break;
	case 17: 
/* #line 275 "compileRagel_preprocessed.rl" */
	{
			printf("end_expression %ld\n", p - input);
			end_expression = p;
		}
/* #line 193 "compileRagel_preprocessed.rl" */
	{
			printf("end_line %ld\n", p - input);
			end_line = p;

			if (name_end && end_expression) {
				if (action_type == ACTION_PARAM) {
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
					compileRagel__param(
						output_end,
						start_line, start_expression - start_line,
						name_start, name_end - name_start,
						end_expression, end_line - end_expression,
						compileRagel__indent, 1, inner_indent_size,
						template_name, template_name_length
					);
					printf("after compileRagel__param\n");
				}
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
			}
			if (action_type == ACTION_NONE) {
				printf(
					"---------- EMPTY ----------\n"
					"line: '%.*s'\n"
					"---------------------------\n",
					end_line - start_line, start_line
				);
				compileRagel__empty(output_end, start_line, end_line - start_line, compileRagel__indent, 1, inner_indent_size);
				printf("after compileRagel__empty\n");
			}

			start_line = NULL;
			end_line = NULL;
			start_expression = NULL;
			end_expression = NULL;
			name_start = NULL;
			name_end = NULL;

		}
	break;
/* #line 938 "compileRagel.c" */
	}
	}

	}

/* #line 301 "compileRagel_preprocessed.rl" */


	compileRagel__end(output_end);
	printf("after compileRagel__end\n");
	*output_end = 0;
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

	CompilationResult *compilation_result = malloc(sizeof(CompilationResult) * 1);
	compilation_result->code = 0;
	compilation_result->message = NULL;
	compilation_result->result = NULL;
	compileRagel_(
		compilation_result,
		name,
		_templates,
		0,
		buffer_size
	);

	PyObject *t = PyTuple_New(3);
	PyTuple_SetItem(t, 0, PyLong_FromLong(compilation_result->code));
	if (compilation_result->message) {
		PyTuple_SetItem(t, 1, PyUnicode_FromString(compilation_result->message));
		PyTuple_SetItem(t, 2, PyUnicode_FromString(""));
	}
	else {
		PyTuple_SetItem(t, 1, PyUnicode_FromString(""));
		PyTuple_SetItem(t, 2, PyUnicode_FromString(compilation_result->result));
	}
	
	free(compilation_result);

	return t;

}