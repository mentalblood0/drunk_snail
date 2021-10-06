char *compile__print_left_part = "result += f'''";
char *compile__print_right_part = "'''\n";

#define compile__cpy_print_left_part() {\
    memcpy(result_end, compile__print_left_part, sizeof(char) * 14);\
    result_end += 14;\
}

#define compile__cpy_print_right_part() {\
    memcpy(result_end, compile__print_right_part, sizeof(char) * 4);\
    result_end += 4;\
}