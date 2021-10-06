char *compile__if_strings[4] = {"if ", " and '", "' in ", ":\n"};
int compile__if_lengths[4] = {3, 6, 5, 2};

#define compile__if_memcpy(i) compile__memcpy(compile__if_strings[i], compile__if_strings[i] + compile__if_lengths[i])

#define compile__cpy_if(param_name_start, param_name_end) {\
	compile__if_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__if_memcpy(1); compile__memcpy(param_name_start, param_name_end);\
	compile__if_memcpy(2); compile__memcpy(template_name, template_name_end);\
	compile__if_memcpy(3);\
}