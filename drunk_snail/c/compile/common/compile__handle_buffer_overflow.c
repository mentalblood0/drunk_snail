#define compile__handle_buffer_overflow() {\
	if (!depth) {\
		free(result);\
	}\
	compilation_result->code = 2;\
	return;\
}