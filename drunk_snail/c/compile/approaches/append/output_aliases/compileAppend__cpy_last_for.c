// if (not P) or (not 'p' in P):
//     result += f'''	<x-:IgnoreComments></x-:IgnoreComments>'''
// elif type(P['p']) != list:
//     result += f'''	<x-:IgnoreComments>{P['p']}</x-:IgnoreComments>'''
// else:
//     for p in P['p']:
//         result += f'''	<x-:IgnoreComments>{p}</x-:IgnoreComments>\n'''



#include "compileAppend__cpy_last_for_l1.c" /* if (not P) or (not 'p' in P): */
#include "compileAppend__cpy_last_for_l3.c" /* elif type(P['p']) != list: */
#include "compileAppend__cpy_last_for_l5.c" /* else: */
#include "compileAppend__cpy_last_for_l6.c" /*     for p in P['p']: */



#define compileAppend__cpy_last_for(param_name_start, param_name_end) {\
	\
	addTabs(&result_end, tabs_number);\
	compileAppend__cpy_last_for_l1(param_name_start, param_name_end);\
	\
	addTabs(&result_end, tabs_number);\
	compile__cpy_one('\t');\
	compileAppend__cpy_print_left_part();\
	addTabs(&result_end, inner_tabs_number);\
	if (prefix_start)\
		compile__memcpy(prefix_start, prefix_end);\
	compile__memcpy(line_before_open_tag_start, line_before_open_tag_end);\
	compile__memcpy(line_after_close_tag_start, line_after_close_tag_end);\
	if (postfix_start)\
		compile__memcpy(postfix_start, postfix_end);\
	compile__cpy_one('\\');\
	compile__cpy_one('n');\
	compileAppend__cpy_print_right_part();\
	\
	addTabs(&result_end, tabs_number);\
	compileAppend__cpy_last_for_l3(param_name_start, param_name_end);\
	\
	addTabs(&result_end, tabs_number);\
	compile__cpy_one('\t');\
	compileAppend__cpy_print_left_part();\
	addTabs(&result_end, inner_tabs_number);\
	if (prefix_start)\
		compile__memcpy(prefix_start, prefix_end);\
	compile__memcpy(line_before_open_tag_start, line_before_open_tag_end);\
	compile__cpy_one('{');\
	compile__memcpy(template_name, template_name_end);\
	compile__cpy_one('['); compile__cpy_one('\'');\
	compile__memcpy(param_name_start, param_name_end);\
	compile__cpy_one('\''); compile__cpy_one(']');\
	compile__cpy_one('}');\
	compile__memcpy(line_after_close_tag_start, line_after_close_tag_end);\
	if (postfix_start)\
		compile__memcpy(postfix_start, postfix_end);\
	compileAppend__cpy_print_right_part();\
	\
	addTabs(&result_end, tabs_number);\
	compileAppend__cpy_last_for_l5();\
	\
	addTabs(&result_end, tabs_number);\
	compileAppend__cpy_last_for_l6(param_name_start, param_name_end);\
	\
	addTabs(&result_end, tabs_number);\
	compile__cpy_one('\t');\
	compile__cpy_one('\t');\
	compileAppend__cpy_print_left_part();\
	addTabs(&result_end, inner_tabs_number);\
	if (prefix_start)\
		compile__memcpy(prefix_start, prefix_end);\
	compile__memcpy(line_before_open_tag_start, line_before_open_tag_end);\
	compile__cpy_one('{');\
	compile__memcpy(param_name_start, param_name_end);\
	compile__cpy_one('}');\
	compile__memcpy(line_after_close_tag_start, line_after_close_tag_end);\
	if (postfix_start)\
		compile__memcpy(postfix_start, postfix_end);\
	compile__cpy_one('\\');\
	compile__cpy_one('n');\
	compileAppend__cpy_print_right_part();\
	\
}