#define compile__cpy_one(c) {\
	if ((result_end - result + 2) >= buffer_size) {\
		if (!depth) {\
			free(result);\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	*result_end = c;\
	result_end++;\
}