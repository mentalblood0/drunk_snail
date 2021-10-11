// "	result += f'''", /* line_start *//* line_end */ "'''
// elif type(", /* P */ "['", /* p */, "']) != list:\
// 	result += f'''", /* line_start */ "{", /* P */ "['", /* p */, "']}", /* line_end */ "'''\
// else:\
// 	for ", /* p */ "in ", /* P */ "['", /* p */, "']:\
// 		result += f'''", /* line_start */"{", /* p */, "}", /* line_end */ "'''\n"

// 	for p in P['p']:



char *compile__last_for_l6_strings[4] = {
	"	for ", /* p */ " in ", /* P */ "['", /* p */ "']:\n"
};


int compile__last_for_l6_lengths[4] = {
	5, 4, 2, 4
};

#define compile__last_for_l6_memcpy(i)\
	compile__memcpy(compile__last_for_l6_strings[i], compile__last_for_l6_strings[i] + compile__last_for_l6_lengths[i]);

#define compile__cpy_last_for_l6(param_name_start, param_name_end) {\
	compile__last_for_l6_memcpy(0); compile__memcpy(param_name_start, param_name_end);\
	compile__last_for_l6_memcpy(1); compile__memcpy(template_name, template_name_end);\
	compile__last_for_l6_memcpy(2); compile__memcpy(param_name_start, param_name_end);\
	compile__last_for_l6_memcpy(3);\
}