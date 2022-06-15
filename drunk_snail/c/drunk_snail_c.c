#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <Python.h>
#include <sys/types.h>

#include "prefix_tree.c"

#include "addTemplate.c"
#include "getTemplate.c"
#include "getTemplateRefs.c"
#include "removeTemplate.c"

#include "chars_to_escape.c"
#include "compile.c"

#include "test.c"

#include "python_module_properties.c"