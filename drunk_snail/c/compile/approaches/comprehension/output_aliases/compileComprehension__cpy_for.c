char *compileComprehension__for_start_strings[1] = {
	"'\\n'.join([\n"
};

int compileComprehension__for_start_lengths[1] = {12};

#define compileComprehension__for_start_memcpy(i) compile__memcpy(compileComprehension__for_start_strings[i], compileComprehension__for_start_strings[i] + compileComprehension__for_start_lengths[i]);

#define compileComprehension__cpy_for_start() {\
	compileComprehension__for_start_memcpy(0);\
};


char *compileComprehension__for_start_unpack_strings[1] = {
	"*[\n"
};

int compileComprehension__for_start_unpack_lengths[1] = {3};

#define compileComprehension__for_start_unpack_memcpy(i) compile__memcpy(compileComprehension__for_start_unpack_strings[i], compileComprehension__for_start_unpack_strings[i] + compileComprehension__for_start_unpack_lengths[i]);

#define compileComprehension__cpy_for_start_unpack() {\
	compileComprehension__for_start_unpack_memcpy(0);\
};


char *compileComprehension__for_end_strings[11] = {
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
	"']]))\n"
};

int compileComprehension__for_end_lengths[11] = {4, 21, 11, 5, 9, 2, 11, 2, 18, 2, 6};

#define compileComprehension__for_end_memcpy(i) compile__memcpy(compileComprehension__for_end_strings[i], compileComprehension__for_end_strings[i] + compileComprehension__for_end_lengths[i]);

#define compileComprehension__cpy_for_end(param_name_start, param_name_end) {\
	compileComprehension__for_end_memcpy(0); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_memcpy(1); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_memcpy(2); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_memcpy(3); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_memcpy(4); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_memcpy(5); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_memcpy(6); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_memcpy(7); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_memcpy(8); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_memcpy(9); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_memcpy(10);\
}


char *compileComprehension__for_end_optional_strings[11] = {
	"for ",
	" in ([] if ((not ",
	") or (not '",
	"' in ",
	")) else (",
	"['",
	"'] if type(",
	"['",
	"']) == list else [",
	"['",
	"']]))\n"
};

int compileComprehension__for_end_optional_lengths[11] = {4, 17, 11, 5, 9, 2, 11, 2, 18, 2, 6};

#define compileComprehension__for_end_optional_memcpy(i) compile__memcpy(compileComprehension__for_end_optional_strings[i], compileComprehension__for_end_optional_strings[i] + compileComprehension__for_end_optional_lengths[i]);

#define compileComprehension__cpy_for_end_optional(param_name_start, param_name_end) {\
	compileComprehension__for_end_optional_memcpy(0); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_optional_memcpy(1); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_optional_memcpy(2); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_optional_memcpy(3); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_optional_memcpy(4); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_optional_memcpy(5); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_optional_memcpy(6); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_optional_memcpy(7); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_optional_memcpy(8); compile__memcpy(template_name, template_name_end);\
	compileComprehension__for_end_optional_memcpy(9); compile__memcpy(param_name_start, param_name_end);\
	compileComprehension__for_end_optional_memcpy(10);\
}