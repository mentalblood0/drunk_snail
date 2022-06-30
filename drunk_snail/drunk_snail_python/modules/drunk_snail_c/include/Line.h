#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "Other.h"



typedef struct {
	char *start;
	char *end;
	char *copy;
	size_t length;
} Token;
typedef struct {
	Token line;
	Token expression;
	Token name;
} Tokens;

typedef bool Flag;
typedef struct {
	Flag optional;
	Flag strict;
} Flags;

typedef enum {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
} Action;

typedef struct {

	Tokens tokens;
	Flags flags;

	Action action;
	Other other;

	bool has_expressions;

} Line;


#define initToken(token) {\
	(token).start = NULL;\
	(token).end = NULL;\
	(token).length = 0;\
	(token).copy = NULL;\
}

#define initFlag(flag) flag = false;

#define initOther(other) {\
	(other).left.start = NULL;\
	(other).left.length = 0;\
	(other).right.start = NULL;\
	(other).right.length = 0;\
}

#define initLine(_line) {\
\
	initToken((_line).tokens.line);\
	initToken((_line).tokens.expression);\
	initToken((_line).tokens.name);\
\
	initFlag((_line).flags.optional);\
	initFlag((_line).flags.strict);\
\
	initOther((_line).other);\
\
	(_line).action = ACTION_NONE;\
\
	(_line).has_expressions = false;\
\
}

#define resetToken(token) {\
	if ((token).copy) {\
		free((token).copy);\
		(token).copy = NULL;\
	}\
	(token).start = NULL;\
	(token).end = NULL;\
}

#define resetFlag(flag) flag = false;

#define resetLine(_line) {\
\
	resetToken((_line).tokens.line);\
	resetToken((_line).tokens.expression);\
	resetToken((_line).tokens.name);\
\
	resetFlag((_line).flags.optional);\
	resetFlag((_line).flags.strict);\
\
	(_line).action = ACTION_NONE;\
\
	(_line).has_expressions = false;\
\
}

#define freeToken(token) {\
	if ((token).copy) {\
		free((token).copy);\
		(token).copy = NULL;\
	}\
}

#define freeLine(_line) {\
	freeToken((_line).tokens.line);\
	freeToken((_line).tokens.expression);\
	freeToken((_line).tokens.name);\
}

#define tokenExists(token) ((token).start && (token).end)

#define allTokensExist(_line) (\
	tokenExists((_line).tokens.line) && \
	tokenExists((_line).tokens.expression) && \
	tokenExists((_line).tokens.name)\
)

#define baseTokensExist(_line) (\
	(_line).tokens.name.end && \
	(_line).tokens.expression.end && \
	(_line).tokens.expression.start\
)

#define verifyAction(_line) {\
	if (!((_line).has_expressions && baseTokensExist(_line))) {\
		(_line).action = ACTION_NONE;\
	}\
}

#define computeOther(_line) {\
	(_line).other.left.start = (_line).tokens.line.start;\
	(_line).other.left.length = (_line).tokens.expression.start - (_line).tokens.line.start;\
	(_line).other.right.start = (_line).tokens.expression.end;\
	(_line).other.right.length = (_line).tokens.line.end - (_line).tokens.expression.end;\
}

#define computeTokenLength(token) {\
	(token).length = (token).end - (token).start;\
}

#define computeTokensLengths(_line) {\
	computeTokenLength((_line).tokens.line);\
	computeTokenLength((_line).tokens.name);\
	computeTokenLength((_line).tokens.expression);\
}