#define compile__chunk_size 65536
#define compile__memcpy(src_start, src_end) {memcpy(result_end, src_start, sizeof(char) * (src_end - src_start)); result_end += src_end - src_start;}

char *compile__print_left_part = "result += f'''";
char *compile__print_right_part = "'''\n";
#define compile__cpy_print_left_part() {memcpy(result_end, compile__print_left_part, sizeof(char) * 14); result_end += 14;}
#define compile__cpy_print_right_part() {memcpy(result_end, compile__print_right_part, sizeof(char) * 4); result_end += 4;}
#define compile__cpy_one(c) {*result_end = c; result_end++;}

char *compile__for_strings[11] = {
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
	"']])):\n"
};
int compile__for_lengths[11] = {4, 21, 11, 5, 9, 2, 11, 2, 18, 2, 7};
#define compile__for_memcpy(i) compile__memcpy(compile__for_strings[i], compile__for_strings[i] + compile__for_lengths[i]);

#define compile__cpy_for(param_name_start, param_name_end) {\
	compile__for_memcpy(0); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(1); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(2); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(3); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(4); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(5); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(6); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(7); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(8); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(9); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(10);\
}

char *compile__def_strings[2] = {"def render(", "):\n\tresult = ''\n"};
int compile__def_lengths[2] = {11, 16};
#define compile__def_memcpy(i) compile__memcpy(compile__def_strings[i], compile__def_strings[i] + compile__def_lengths[i])

#define compile__cpy_def() {\
	compile__def_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__def_memcpy(1);\
}

char *compile__if_strings[4] = {"if ", " and '", "' in ", ":\n"};
int compile__if_lengths[4] = {3, 6, 5, 2};
#define compile__if_memcpy(i) compile__memcpy(compile__if_strings[i], compile__if_strings[i] + compile__if_lengths[i])

#define compile__cpy_if(param_name_start, param_name_end) {\
	compile__if_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__if_memcpy(1); compile__memcpy(param_name_start, param_name_end);\
	compile__if_memcpy(2); compile__memcpy(template_name, template_name_end);\
	compile__if_memcpy(3);\
}

char *compile__return = "\treturn result\n";
int compile__return_length = 15;