int compile__addTabs__i;
#define compile__addTabs(s_end, n) {\
	if ((result_end - result + n) >= buffer_size) {\
		if (!depth) {\
			free(result);\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	for (compile__addTabs__i = 0; compile__addTabs__i < n; compile__addTabs__i++) {\
		*result_end = '\t';\
		result_end++;\
	}\
}