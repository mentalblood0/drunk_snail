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