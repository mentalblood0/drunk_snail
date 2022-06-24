#pragma once

#include <stdbool.h>
#include <sys/types.h>



typedef struct {
	char *start;
	char *end;
	char *copy;
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

} Line;


#define initToken(token) {\
	(token).start = NULL;\
	(token).end = NULL;\
	(token).copy = NULL;\
}

#define initFlag(flag) flag = false;

#define initLine(_line) {\
\
	initToken((_line).tokens.line);\
	initToken((_line).tokens.expression);\
	initToken((_line).tokens.name);\
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
	if (!baseTokensExist(_line)) {\
		(_line).action = ACTION_NONE;\
	}\
}