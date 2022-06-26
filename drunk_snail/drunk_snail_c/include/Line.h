#pragma once

#include <stdbool.h>
#include <sys/types.h>



typedef struct {
	char *start;
	char *end;
	char *copy;
	size_t length;
} Token;
typedef struct {
	Token left;
	Token right;
} Other;
typedef struct {
	Token line;
	Token expression;
	Token name;
	Other other;
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

} Line;


#define initToken(token) {\
	(token).start = NULL;\
	(token).end = NULL;\
	(token).length = 0;\
	(token).copy = NULL;\
}

#define initFlag(flag) flag = false;

#define initLine(_line) {\
\
	initToken((_line).tokens.line);\
	initToken((_line).tokens.expression);\
	initToken((_line).tokens.name);\
	initToken((_line).tokens.other.left);\
	initToken((_line).tokens.other.right);\
\
	initFlag((_line).flags.optional);\
	initFlag((_line).flags.strict);\
\
	(_line).action = ACTION_NONE;\
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
	resetToken((_line).tokens.other.left);\
	resetToken((_line).tokens.other.right);\
\
	resetFlag((_line).flags.optional);\
	resetFlag((_line).flags.strict);\
\
	(_line).action = ACTION_NONE;\
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
	freeToken((_line).tokens.other.left);\
	freeToken((_line).tokens.other.right);\
}

#define baseTokensExist(_line) (\
	(_line).tokens.name.end && \
	(_line).tokens.expression.end && \
	(_line).tokens.expression.start\
)

#define verifyAction(_line) {\
	if (!baseTokensExist(_line)) {\
		(_line).action = ACTION_NONE;\
	}\
}

#define addOtherTokens(_line) {\
	(_line).tokens.other.left.start = (_line).tokens.line.start;\
	(_line).tokens.other.left.length = (_line).tokens.expression.start - (_line).tokens.line.start;\
	(_line).tokens.other.right.start = (_line).tokens.expression.end;\
	(_line).tokens.other.right.length = (_line).tokens.line.end - (_line).tokens.expression.end;\
}

#define computeTokenLength(token) {\
	(token).length = (token).end - (token).start;\
}

#define computeTokensLengths(_line) {\
	computeTokenLength((_line).tokens.line);\
	computeTokenLength((_line).tokens.name);\
	computeTokenLength((_line).tokens.expression);\
}