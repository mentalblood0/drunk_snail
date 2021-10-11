// if (not P) or (not 'p' in P):



char *compile__last_for_l1_strings[4] = {
	"if (not ", /* P */ ") or (not '", /* p */ "' in ", /* P */ "):\n"
};


int compile__last_for_l1_lengths[4] = {
	8, 11, 5, 3
};

#define compile__last_for_l1_memcpy(i)\
	compile__memcpy(compile__last_for_l1_strings[i], compile__last_for_l1_strings[i] + compile__last_for_l1_lengths[i]);

#define compile__cpy_last_for_l1(param_name_start, param_name_end) {\
	compile__last_for_l1_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__last_for_l1_memcpy(1); compile__memcpy(param_name_start, param_name_end);\
	compile__last_for_l1_memcpy(2); compile__memcpy(template_name, template_name_end);\
	compile__last_for_l1_memcpy(3);\
}