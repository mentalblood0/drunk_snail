char *compile__def_strings[2] = {"def render(", "):\n\tresult = ''\n"};
int compile__def_lengths[2] = {11, 16};

#define compile__def_memcpy(i) compile__memcpy(compile__def_strings[i], compile__def_strings[i] + compile__def_lengths[i])

#define compile__cpy_def() {\
	compile__def_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__def_memcpy(1);\
}