char *compileAppend__def_strings[2] = {"def render(", "):\n\tresult = []\n"};
int compileAppend__def_lengths[2] = {11, 16};

#define compileAppend__def_memcpy(i) compile__memcpy(compileAppend__def_strings[i], compileAppend__def_strings[i] + compileAppend__def_lengths[i])

#define compileAppend__cpy_def() {\
	compileAppend__def_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compileAppend__def_memcpy(1);\
}