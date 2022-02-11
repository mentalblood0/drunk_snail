char *compile__print_left_part = "result.append(f'''";
char *compile__print_right_part = "''')\n";

#define compile__cpy_print_left_part() {\
    compile__memcpy(compile__print_left_part, compile__print_left_part + 18);\
}

#define compile__cpy_print_right_part() {\
    compile__memcpy(compile__print_right_part, compile__print_right_part + 5);\
}