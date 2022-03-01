
#line 1 "test_preprocessed.rl"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


#line 10 "test.c"
static const int compile_start = 0;
static const int compile_first_final = 0;
static const int compile_error = -1;

static const int compile_en_main = 0;


#line 9 "test_preprocessed.rl"




char *compileComprehension__def_strings[2] = {
	"J='\\n'.join\ndef render(",
	"):\n\treturn J(["
};
#define compileComprehension__def(target, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	if ((*target - compilation_result->result) + (23+TEMPLATE_NAME_length+14+1) >= buffer_size) {\
		if (!depth) {\
			free(compilation_result->result);\
			compilation_result->result = NULL;\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	memcpy(*target, compileComprehension__def_strings[0], 23); *target += 23;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, compileComprehension__def_strings[1], 14); *target += 14;\
};

char *compileComprehension__end_strings[1] = {
	"])"
};
#define compileComprehension__end(target) {\
	if ((*target - compilation_result->result) + (2+1) >= buffer_size) {\
		if (!depth) {\
			free(compilation_result->result);\
			compilation_result->result = NULL;\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	memcpy(*target, compileComprehension__end_strings[0], 2); *target += 2;\
};

char *compileComprehension__for_strings[12] = {
	"for ",
	" in ([",
	"] if ((not ",
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
#define compileComprehension__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	if ((*target - compilation_result->result) + (4+ARG_length+6+4+11+TEMPLATE_NAME_length+11+ARG_length+5+TEMPLATE_NAME_length+9+TEMPLATE_NAME_length+2+ARG_length+11+TEMPLATE_NAME_length+2+ARG_length+18+TEMPLATE_NAME_length+2+ARG_length+5+1) >= buffer_size) {\
		if (!depth) {\
			free(compilation_result->result);\
			compilation_result->result = NULL;\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	memcpy(*target, compileComprehension__for_strings[0], 4); *target += 4;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, compileComprehension__for_strings[1], 6); *target += 6;\
	if (optional) {\
		memcpy(*target, "", 0); *target += 0;\
	}\
	else {\
		memcpy(*target, "None", 4); *target += 4;\
	}\
	memcpy(*target, compileComprehension__for_strings[2], 11); *target += 11;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, compileComprehension__for_strings[3], 11); *target += 11;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, compileComprehension__for_strings[4], 5); *target += 5;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, compileComprehension__for_strings[5], 9); *target += 9;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, compileComprehension__for_strings[6], 2); *target += 2;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, compileComprehension__for_strings[7], 11); *target += 11;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, compileComprehension__for_strings[8], 2); *target += 2;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, compileComprehension__for_strings[9], 18); *target += 18;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, compileComprehension__for_strings[10], 2); *target += 2;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, compileComprehension__for_strings[11], 5); *target += 5;\
};


char *compileComprehension__empty_strings[2] = {
	"\"",
	"\","
};
#define compileComprehension__empty(target, LINE, LINE_length) {\
	if ((*target - compilation_result->result) + (1+LINE_length+2+1) >= buffer_size) {\
		if (!depth) {\
			free(compilation_result->result);\
			compilation_result->result = NULL;\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	memcpy(*target, compileComprehension__empty_strings[0], 1); *target += 1;\
	memcpy(*target, LINE, LINE_length); *target += LINE_length;\
	memcpy(*target, compileComprehension__empty_strings[1], 2); *target += 2;\
};

char *compileComprehension__param_strings[5] = {
	"*[f\"",
	"{",
	"}",
	"\"",
	"],"
};
#define compileComprehension__param(target, OTHER_LEFT, OTHER_LEFT_length, ARG, ARG_length, OTHER_RIGHT, OTHER_RIGHT_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	if ((*target - compilation_result->result) + (4+OTHER_LEFT_length+1+ARG_length+1+OTHER_RIGHT_length+1+4+ARG_length+6+4+11+TEMPLATE_NAME_length+11+ARG_length+5+TEMPLATE_NAME_length+9+TEMPLATE_NAME_length+2+ARG_length+11+TEMPLATE_NAME_length+2+ARG_length+18+TEMPLATE_NAME_length+2+ARG_length+5+2+1) >= buffer_size) {\
		if (!depth) {\
			free(compilation_result->result);\
			compilation_result->result = NULL;\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	memcpy(*target, compileComprehension__param_strings[0], 4); *target += 4;\
	memcpy(*target, OTHER_LEFT, OTHER_LEFT_length); *target += OTHER_LEFT_length;\
	memcpy(*target, compileComprehension__param_strings[1], 1); *target += 1;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, compileComprehension__param_strings[2], 1); *target += 1;\
	memcpy(*target, OTHER_RIGHT, OTHER_RIGHT_length); *target += OTHER_RIGHT_length;\
	memcpy(*target, compileComprehension__param_strings[3], 1); *target += 1;\
	compileComprehension__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	memcpy(*target, compileComprehension__param_strings[4], 2); *target += 2;\
};

char *compileComprehension__ref_before_strings[4] = {
	"*[\"",
	"\"+\"",
	"\\n",
	"\".join(["
};
#define compileComprehension__ref_before(target, OTHER_LEFT, OTHER_LEFT_length, OTHER_RIGHT, OTHER_RIGHT_length) {\
	if ((*target - compilation_result->result) + (3+OTHER_LEFT_length+3+OTHER_RIGHT_length+2+OTHER_LEFT_length+8+1) >= buffer_size) {\
		if (!depth) {\
			free(compilation_result->result);\
			compilation_result->result = NULL;\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	memcpy(*target, compileComprehension__ref_before_strings[0], 3); *target += 3;\
	memcpy(*target, OTHER_LEFT, OTHER_LEFT_length); *target += OTHER_LEFT_length;\
	memcpy(*target, compileComprehension__ref_before_strings[1], 3); *target += 3;\
	memcpy(*target, OTHER_RIGHT, OTHER_RIGHT_length); *target += OTHER_RIGHT_length;\
	memcpy(*target, compileComprehension__ref_before_strings[2], 2); *target += 2;\
	memcpy(*target, OTHER_LEFT, OTHER_LEFT_length); *target += OTHER_LEFT_length;\
	memcpy(*target, compileComprehension__ref_before_strings[3], 8); *target += 8;\
};

char *compileComprehension__ref_after_strings[3] = {
	"])+\"",
	"\"",
	"],"
};
#define compileComprehension__ref_after(target, OTHER_RIGHT, OTHER_RIGHT_length, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	if ((*target - compilation_result->result) + (4+OTHER_RIGHT_length+1+4+ARG_length+6+4+11+TEMPLATE_NAME_length+11+ARG_length+5+TEMPLATE_NAME_length+9+TEMPLATE_NAME_length+2+ARG_length+11+TEMPLATE_NAME_length+2+ARG_length+18+TEMPLATE_NAME_length+2+ARG_length+5+2+1) >= buffer_size) {\
		if (!depth) {\
			free(compilation_result->result);\
			compilation_result->result = NULL;\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	memcpy(*target, compileComprehension__ref_after_strings[0], 4); *target += 4;\
	memcpy(*target, OTHER_RIGHT, OTHER_RIGHT_length); *target += OTHER_RIGHT_length;\
	memcpy(*target, compileComprehension__ref_after_strings[1], 1); *target += 1;\
	compileComprehension__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	memcpy(*target, compileComprehension__ref_after_strings[2], 2); *target += 2;\
};


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
	Tree *templates_tree,
	char **output_end,
	int depth,
	int buffer_size
)
{

	Template *template = dictionaryLookupUnterminated(templates_tree, template_name, template_name_length);
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

	if (compilation_result->result == NULL) {
		compilation_result->result = malloc(sizeof(char) * buffer_size);
		output_end = malloc(sizeof(char*) * 1);
		*output_end = compilation_result->result;
	}

	if (!depth) {
		clearRefs(template);
		compileComprehension__def(output_end, template_name, template_name_length);
	}

	
#line 267 "test.c"
	{
	cs = compile_start;
	}

#line 272 "test.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr1:
#line 258 "test_preprocessed.rl"
	{ start_line = p; }
#line 259 "test_preprocessed.rl"
	{

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
					compileComprehension__ref_after(output_end, end_expression, end_line - end_expression, name_start, name_end - name_start, template_name, template_name_length);
				}
			}
			if (action_type == ACTION_NONE)
				compileComprehension__empty(output_end, start_line, end_line - start_line);

			reset_line_properties();

		}
	goto st0;
tr4:
#line 259 "test_preprocessed.rl"
	{

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
					compileComprehension__ref_after(output_end, end_expression, end_line - end_expression, name_start, name_end - name_start, template_name, template_name_length);
				}
			}
			if (action_type == ACTION_NONE)
				compileComprehension__empty(output_end, start_line, end_line - start_line);

			reset_line_properties();

		}
	goto st0;
tr31:
#line 314 "test_preprocessed.rl"
	{ end_expression = p; }
#line 259 "test_preprocessed.rl"
	{

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
					compileComprehension__ref_after(output_end, end_expression, end_line - end_expression, name_start, name_end - name_start, template_name, template_name_length);
				}
			}
			if (action_type == ACTION_NONE)
				compileComprehension__empty(output_end, start_line, end_line - start_line);

			reset_line_properties();

		}
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 424 "test.c"
	switch( (*p) ) {
		case 10: goto tr1;
		case 60: goto tr2;
	}
	goto tr0;
tr0:
#line 258 "test_preprocessed.rl"
	{ start_line = p; }
	goto st1;
tr30:
#line 314 "test_preprocessed.rl"
	{ end_expression = p; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 442 "test.c"
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
	}
	goto st1;
tr2:
#line 258 "test_preprocessed.rl"
	{ start_line = p; }
#line 310 "test_preprocessed.rl"
	{
			if (!(start_expression && name_end))
				start_expression = p;
		}
	goto st2;
tr5:
#line 310 "test_preprocessed.rl"
	{
			if (!(start_expression && name_end))
				start_expression = p;
		}
	goto st2;
tr32:
#line 310 "test_preprocessed.rl"
	{
			if (!(start_expression && name_end))
				start_expression = p;
		}
#line 314 "test_preprocessed.rl"
	{ end_expression = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 477 "test.c"
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
tr21:
#line 305 "test_preprocessed.rl"
	{ optional = true; }
	goto st6;
tr38:
#line 303 "test_preprocessed.rl"
	{ action_type = ACTION_PARAM; }
	goto st6;
tr43:
#line 304 "test_preprocessed.rl"
	{ action_type = ACTION_REF; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 531 "test.c"
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st7;
		case 112: goto st21;
		case 114: goto st27;
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
		case 40: goto tr21;
		case 60: goto tr5;
		case 95: goto tr22;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr22;
	} else if ( (*p) >= 65 )
		goto tr22;
	goto st1;
tr22:
#line 305 "test_preprocessed.rl"
	{ optional = true; }
#line 307 "test_preprocessed.rl"
	{ name_start = p; }
	goto st16;
tr39:
#line 303 "test_preprocessed.rl"
	{ action_type = ACTION_PARAM; }
#line 307 "test_preprocessed.rl"
	{ name_start = p; }
	goto st16;
tr44:
#line 304 "test_preprocessed.rl"
	{ action_type = ACTION_REF; }
#line 307 "test_preprocessed.rl"
	{ name_start = p; }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 658 "test.c"
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto tr23;
		case 45: goto tr24;
		case 60: goto tr5;
		case 95: goto st16;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st16;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st16;
	} else
		goto st16;
	goto st1;
tr23:
#line 308 "test_preprocessed.rl"
	{ name_end = p; }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 683 "test.c"
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st17;
		case 45: goto st18;
		case 60: goto tr5;
	}
	goto st1;
tr24:
#line 308 "test_preprocessed.rl"
	{ name_end = p; }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 699 "test.c"
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st19;
		case 60: goto tr5;
	}
	goto st1;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 62: goto st20;
	}
	goto st1;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	switch( (*p) ) {
		case 10: goto tr31;
		case 60: goto tr32;
	}
	goto tr30;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st22;
	}
	goto st1;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st23;
	}
	goto st1;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st24;
	}
	goto st1;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 109: goto st25;
	}
	goto st1;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st26;
		case 60: goto tr5;
	}
	goto st1;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr38;
		case 60: goto tr5;
		case 95: goto tr39;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr39;
	} else if ( (*p) >= 65 )
		goto tr39;
	goto st1;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 101: goto st28;
	}
	goto st1;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 102: goto st29;
	}
	goto st1;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st30;
		case 60: goto tr5;
	}
	goto st1;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr43;
		case 60: goto tr5;
		case 95: goto tr44;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr44;
	} else if ( (*p) >= 65 )
		goto tr44;
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
#line 259 "test_preprocessed.rl"
	{

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
					compileComprehension__ref_after(output_end, end_expression, end_line - end_expression, name_start, name_end - name_start, template_name, template_name_length);
				}
			}
			if (action_type == ACTION_NONE)
				compileComprehension__empty(output_end, start_line, end_line - start_line);

			reset_line_properties();

		}
	break;
	case 20: 
#line 314 "test_preprocessed.rl"
	{ end_expression = p; }
#line 259 "test_preprocessed.rl"
	{

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
					compileComprehension__ref_after(output_end, end_expression, end_line - end_expression, name_start, name_end - name_start, template_name, template_name_length);
				}
			}
			if (action_type == ACTION_NONE)
				compileComprehension__empty(output_end, start_line, end_line - start_line);

			reset_line_properties();

		}
	break;
#line 996 "test.c"
	}
	}

	}

#line 337 "test_preprocessed.rl"


	if (!depth) {
		compileComprehension__end(output_end);
		**output_end = 0;
		free(output_end);
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

	CompilationResult *compilation_result = malloc(sizeof(CompilationResult) * 1);
	compilation_result->code = 0;
	compilation_result->message = NULL;
	compilation_result->result = NULL;
	compileComprehension_(
		compilation_result,
		name,
		strlen(name),
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