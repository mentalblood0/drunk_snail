#define compile__cpy_one(c) {\
	if ((result_end - result) >= buffer_size) {\
		if (!depth) {\
			free(result);\
		}\
		compilation_result->code = 2;\
		return;\
	}\
	*result_end = c;\
	result_end++;\
}


#define compile__cpy_one_no_check(c) {\
	*result_end = c;\
	result_end++;\
}