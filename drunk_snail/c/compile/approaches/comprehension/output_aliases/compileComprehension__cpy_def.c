char *compileComprehension__def_strings[2] = {"def render(", "):\n\treturn '\\n'.join(["};
int compileComprehension__def_lengths[2] = {11, 22};

#define compileComprehension__def_memcpy(i) compile__memcpy(compileComprehension__def_strings[i], compileComprehension__def_strings[i] + compileComprehension__def_lengths[i])

#define compileComprehension__cpy_def() {\
	compileComprehension__def_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compileComprehension__def_memcpy(1);\
}