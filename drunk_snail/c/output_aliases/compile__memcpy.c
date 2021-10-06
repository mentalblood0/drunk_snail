#define compile__memcpy(src_start, src_end) {\
    if ((result_end + (src_end - src_start)) - result + 2 >= buffer_size) {\
        fprintf(stderr, "buffer overflow, result=%p\n", result);\
        if (!depth)\
            free(result);\
        fprintf(stderr, "returning NULL\n");\
        return NULL;\
    }\
    memcpy(result_end, src_start, sizeof(char) * (src_end - src_start));\
    result_end += src_end - src_start;\
}