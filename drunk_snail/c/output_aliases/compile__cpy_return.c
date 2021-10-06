char *compile__return = "\treturn result\n";

#define compile__cpy_return() compile__memcpy(compile__return, compile__return + 15);