char *compileAppend__for_strings[11] = {
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

int compileAppend__for_lengths[11] = {4, 21, 11, 5, 9, 2, 11, 2, 18, 2, 7};

#define compileAppend__for_memcpy(i) compile__memcpy(compileAppend__for_strings[i], compileAppend__for_strings[i] + compileAppend__for_lengths[i]);

#define compileAppend__cpy_for(param_name_start, param_name_end) {\
	compileAppend__for_memcpy(0); compile__memcpy(param_name_start, param_name_end);\
	compileAppend__for_memcpy(1); compile__memcpy(template_name, template_name_end);\
	compileAppend__for_memcpy(2); compile__memcpy(param_name_start, param_name_end);\
	compileAppend__for_memcpy(3); compile__memcpy(template_name, template_name_end);\
	compileAppend__for_memcpy(4); compile__memcpy(template_name, template_name_end);\
	compileAppend__for_memcpy(5); compile__memcpy(param_name_start, param_name_end);\
	compileAppend__for_memcpy(6); compile__memcpy(template_name, template_name_end);\
	compileAppend__for_memcpy(7); compile__memcpy(param_name_start, param_name_end);\
	compileAppend__for_memcpy(8); compile__memcpy(template_name, template_name_end);\
	compileAppend__for_memcpy(9); compile__memcpy(param_name_start, param_name_end);\
	compileAppend__for_memcpy(10);\
}