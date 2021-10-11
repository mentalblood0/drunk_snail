// elif type(P['p']) != list:



char *compile__last_for_l3_strings[4] = {
	"elif type(", /* P */ "['", /* p */ "']) != list:\n"
};


int compile__last_for_l3_lengths[4] = {
	10, 2, 13
};

#define compile__last_for_l3_memcpy(i)\
	compile__memcpy(compile__last_for_l3_strings[i], compile__last_for_l3_strings[i] + compile__last_for_l3_lengths[i]);

#define compile__cpy_last_for_l3(param_name_start, param_name_end) {\
	compile__last_for_l3_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__last_for_l3_memcpy(1); compile__memcpy(param_name_start, param_name_end);\
	compile__last_for_l3_memcpy(2);\
}