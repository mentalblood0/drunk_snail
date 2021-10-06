#define compile__memcpy(src_start, src_end) {\
    memcpy(result_end, src_start, sizeof(char) * (src_end - src_start));\
    result_end += src_end - src_start;\
}