char *compile__return = "\treturn ''.join(result)\n";

#define compile__cpy_return() compile__memcpy(compile__return, compile__return + 24);