
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


static const int compile_start = 0;
static const int compile_first_final = 0;
static const int compile_error = -1;

static const int compile_en_main = 0;






#define compile__def(target, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	while ((*target - compilation_result->result) + (23+TEMPLATE_NAME_length+14+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "J='\\n'.join\ndef render(", 23); *target += 23;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, "):\n\treturn J([", 14); *target += 14;\
};

#define compile__end(target) {\
	while ((*target - compilation_result->result) + (2+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "])", 2); *target += 2;\
};

#define compile__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	while ((*target - compilation_result->result) + (4+ARG_length+5+TEMPLATE_NAME_length+2+ARG_length+16+TEMPLATE_NAME_length+2+ARG_length+8+TEMPLATE_NAME_length+2+ARG_length+7+ARG_length+4+TEMPLATE_NAME_length+6+2+2+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "for ", 4); *target += 4;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, " in((", 5); *target += 5;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, "['", 2); *target += 2;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, "']if list==type(", 16); *target += 16;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, "['", 2); *target += 2;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, "'])else[", 8); *target += 8;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, "['", 2); *target += 2;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, "']])if'", 7); *target += 7;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, "'in ", 4); *target += 4;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, " else[", 6); *target += 6;\
	if (optional) {\
		memcpy(*target, "", 0); *target += 0;\
	}\
	else {\
		memcpy(*target, "''", 2); *target += 2;\
	}\
	memcpy(*target, "])", 2); *target += 2;\
};

#define compile__for_strict(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	while ((*target - compilation_result->result) + (4+ARG_length+4+TEMPLATE_NAME_length+2+ARG_length+2+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "for ", 4); *target += 4;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, " in ", 4); *target += 4;\
	memcpy(*target, TEMPLATE_NAME, TEMPLATE_NAME_length); *target += TEMPLATE_NAME_length;\
	memcpy(*target, "['", 2); *target += 2;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, "']", 2); *target += 2;\
};


int compile__empty__i;
#define compile__empty(target, LINE, LINE_length) {\
	while ((*target - compilation_result->result) + (3+0+LINE_length+0+4+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "'''", 3); *target += 3;\
	for (compile__empty__i = 0; compile__empty__i < depth; compile__empty__i++) {\
		memcpy(*target, other[compile__empty__i].left.start, other[compile__empty__i].left.length); *target += other[compile__empty__i].left.length;\
	}\
	memcpy(*target, "", 0); *target += 0;\
	memcpy(*target, LINE, LINE_length); *target += LINE_length;\
	memcpy(*target, "", 0); *target += 0;\
	for (compile__empty__i = depth-1; compile__empty__i >= 0; compile__empty__i--) {\
		memcpy(*target, other[compile__empty__i].right.start, other[compile__empty__i].right.length); *target += other[compile__empty__i].right.length;\
	}\
	memcpy(*target, "''',", 4); *target += 4;\
};

int compile__param__i;
#define compile__param(target, OTHER_LEFT, OTHER_LEFT_length, ARG, ARG_length, OTHER_RIGHT, OTHER_RIGHT_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	while ((*target - compilation_result->result) + (6+0+OTHER_LEFT_length+1+ARG_length+1+OTHER_RIGHT_length+0+3+4+ARG_length+5+TEMPLATE_NAME_length+2+ARG_length+16+TEMPLATE_NAME_length+2+ARG_length+8+TEMPLATE_NAME_length+2+ARG_length+7+ARG_length+4+TEMPLATE_NAME_length+6+2+2+2+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "*[f'''", 6); *target += 6;\
	for (compile__param__i = 0; compile__param__i < depth; compile__param__i++) {\
		memcpy(*target, other[compile__param__i].left.start, other[compile__param__i].left.length); *target += other[compile__param__i].left.length;\
	}\
	memcpy(*target, "", 0); *target += 0;\
	memcpy(*target, OTHER_LEFT, OTHER_LEFT_length); *target += OTHER_LEFT_length;\
	memcpy(*target, "{", 1); *target += 1;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, "}", 1); *target += 1;\
	memcpy(*target, OTHER_RIGHT, OTHER_RIGHT_length); *target += OTHER_RIGHT_length;\
	memcpy(*target, "", 0); *target += 0;\
	for (compile__param__i = depth-1; compile__param__i >= 0; compile__param__i--) {\
		memcpy(*target, other[compile__param__i].right.start, other[compile__param__i].right.length); *target += other[compile__param__i].right.length;\
	}\
	memcpy(*target, "'''", 3); *target += 3;\
	if (strict) {\
		compile__for_strict(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	}\
	else {\
		compile__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	}\
	memcpy(*target, "],", 2); *target += 2;\
};

#define compile__ref_before(target) {\
	while ((*target - compilation_result->result) + (5+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "*[J([", 5); *target += 5;\
};

#define compile__ref_after(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length) {\
	while ((*target - compilation_result->result) + (2+4+ARG_length+5+TEMPLATE_NAME_length+2+ARG_length+16+TEMPLATE_NAME_length+2+ARG_length+8+TEMPLATE_NAME_length+2+ARG_length+7+ARG_length+4+TEMPLATE_NAME_length+6+2+2+2+1) >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - compilation_result->result);\
		compilation_result->result = new_result;\
	}\
	memcpy(*target, "])", 2); *target += 2;\
	if (strict) {\
		compile__for_strict(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	}\
	else {\
		compile__for(target, ARG, ARG_length, TEMPLATE_NAME, TEMPLATE_NAME_length);\
	}\
	memcpy(*target, "],", 2); *target += 2;\
};


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

	
	{
	cs = compile_start;
	}

	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr1:
	{ start_line = p; }
	{

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
	goto st0;
tr4:
	{

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
	goto st0;
tr32:
	{ end_expression = p; }
	{

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
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	switch( (*p) ) {
		case 10: goto tr1;
		case 60: goto tr2;
	}
	goto tr0;
tr0:
	{ start_line = p; }
	goto st1;
tr31:
	{ end_expression = p; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
	}
	goto st1;
tr2:
	{ start_line = p; }
	{
			if (!(start_expression && name_end))
				start_expression = p;
		}
	goto st2;
tr5:
	{
			if (!(start_expression && name_end))
				start_expression = p;
		}
	goto st2;
tr33:
	{
			if (!(start_expression && name_end))
				start_expression = p;
		}
	{ end_expression = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
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
	{ optional = true; }
	goto st6;
tr39:
	{ action_type = ACTION_PARAM; }
	goto st6;
tr44:
	{ action_type = ACTION_REF; }
	goto st6;
tr52:
	{ strict = true; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st7;
		case 112: goto st21;
		case 114: goto st27;
		case 115: goto st31;
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
		case 95: goto tr23;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr23;
	} else if ( (*p) >= 65 )
		goto tr23;
	goto st1;
tr23:
	{ optional = true; }
	{ name_start = p; }
	goto st16;
tr40:
	{ action_type = ACTION_PARAM; }
	{ name_start = p; }
	goto st16;
tr45:
	{ action_type = ACTION_REF; }
	{ name_start = p; }
	goto st16;
tr53:
	{ strict = true; }
	{ name_start = p; }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto tr24;
		case 45: goto tr25;
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
tr24:
	{ name_end = p; }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st17;
		case 45: goto st18;
		case 60: goto tr5;
	}
	goto st1;
tr25:
	{ name_end = p; }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
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
		case 10: goto tr32;
		case 60: goto tr33;
	}
	goto tr31;
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
		case 40: goto tr39;
		case 60: goto tr5;
		case 95: goto tr40;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr40;
	} else if ( (*p) >= 65 )
		goto tr40;
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
		case 40: goto tr44;
		case 60: goto tr5;
		case 95: goto tr45;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr45;
	} else if ( (*p) >= 65 )
		goto tr45;
	goto st1;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st32;
	}
	goto st1;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st33;
	}
	goto st1;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st34;
	}
	goto st1;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 99: goto st35;
	}
	goto st1;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st36;
	}
	goto st1;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st37;
		case 60: goto tr5;
	}
	goto st1;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr52;
		case 60: goto tr5;
		case 95: goto tr53;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr53;
	} else if ( (*p) >= 65 )
		goto tr53;
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
	case 31: 
	case 32: 
	case 33: 
	case 34: 
	case 35: 
	case 36: 
	case 37: 
	{

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
	break;
	case 20: 
	{ end_expression = p; }
	{

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
	break;
	}
	}

	}



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