// if (not P) or (not 'p' in P):



char *compileAppend__last_for_l1_strings[4] = {
	"if (not ", /* P */ ") or (not '", /* p */ "' in ", /* P */ "):\n"
};


int compileAppend__last_for_l1_lengths[4] = {
	8, 11, 5, 3
};

#define compileAppend__last_for_l1_memcpy(i)\
	compile__memcpy(compileAppend__last_for_l1_strings[i], compileAppend__last_for_l1_strings[i] + compileAppend__last_for_l1_lengths[i]);

#define compileAppend__cpy_last_for_l1(param_name_start, param_name_end) {\
	compileAppend__last_for_l1_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compileAppend__last_for_l1_memcpy(1); compile__memcpy(param_name_start, param_name_end);\
	compileAppend__last_for_l1_memcpy(2); compile__memcpy(template_name, template_name_end);\
	compileAppend__last_for_l1_memcpy(3);\
}