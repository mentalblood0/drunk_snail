#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <Python.h>
#include <sys/types.h>

#include "prefix_tree.c"

#include "Keywords.c"
#include "addTemplate.c"
#include "getTemplate.c"
#include "getTemplateRefs.c"
#include "removeTemplate.c"
#include "addKeyword.c"
#include "removeKeyword.c"
#include "./compile/main.c"

#include "python_module_properties.c"