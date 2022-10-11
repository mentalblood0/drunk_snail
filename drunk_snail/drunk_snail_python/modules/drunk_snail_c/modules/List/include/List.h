#pragma once

#include <stdlib.h>

#include "../../memoma/include/memoma.h"



#define listDefine(TYPE, NAME) typedef struct {\
	TYPE *start;\
	TYPE *temp;\
	size_t length;\
	size_t allocated;\
} NAME;


#define listCreate(target, TYPE, initial_length, alloc_error) {\
	drunk_malloc_one((target).start, sizeof(TYPE) * (initial_length), alloc_error);\
	if (!alloc_error) {\
		(target).length = 0;\
		(target).allocated = initial_length;\
	}\
}

#define listGetNew(target, TYPE, result_target, alloc_error) {\
	listExtend(target, TYPE, alloc_error);\
	if (alloc_error) {\
		result_target = NULL;\
		exit__parse();\
	} else {\
		result_target = (target).start + (target).length - 1;\
	}\
}

#define listExtend(target, TYPE, alloc_error) {\
	if ((target).length == (target).allocated) {\
		(target).allocated *= 4;\
		drunk_realloc_one((target).start, sizeof(TYPE) * (target).allocated, (target).temp, alloc_error);\
		if (!alloc_error) {\
			(target).length += 1;\
		} else {\
			exit__parse();\
		}\
	} else {\
		(target).length += 1;\
	}\
}

#define listPush(target, TYPE, element, alloc_error) {\
	if ((target).length == (target).allocated) {\
		(target).allocated *= 2;\
		drunk_realloc_one((target).start, sizeof(TYPE) * (target).allocated, (target).temp, alloc_error);\
		if (!alloc_error) {\
			(target).start[(target).length] = element;\
			(target).length += 1;\
		} else {\
			exit_render_();\
		}\
	} else {\
		(target).start[(target).length] = element;\
		(target).length += 1;\
	}\
}

#define listSet(target, TYPE, i, element, alloc_error) {\
	if (i >= (target).length) {\
		listPush(target, TYPE, element, alloc_error);\
	} else {\
		(target).start[i] = element;\
	}\
}

#define listClear(target) {\
	(target).length = 0;\
}

#define listFree(target) {\
	if ((target).start) {\
		free((target).start);\
		(target).start = NULL;\
	}\
}