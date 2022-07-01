#define PY_SSIZE_T_CLEAN
#include <Python.h>



PyMethodDef methods[6];
struct PyModuleDef drunk_snail_c_module;

PyMODINIT_FUNC PyInit_drunk_snail_c(void);