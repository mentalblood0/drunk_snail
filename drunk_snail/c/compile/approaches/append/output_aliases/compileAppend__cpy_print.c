char *compileAppend__print_left_part = "result.append(f'''";
char *compileAppend__print_right_part = "''')\n";

#define compileAppend__cpy_print_left_part() {\
    compile__memcpy(compileAppend__print_left_part, compileAppend__print_left_part + 18);\
}

#define compileAppend__cpy_print_right_part() {\
    compile__memcpy(compileAppend__print_right_part, compileAppend__print_right_part + 5);\
}