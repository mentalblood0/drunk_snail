#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "Other.h"
#include "../modules/List/include/List.h"



typedef struct {
	char *start;
	char *end;
	char *copy;
	size_t length;
} Token;
typedef struct {
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
} Expression;

listDefine(Expression, ExpressionList);

typedef struct {

	Expression single_expression;
	ExpressionList *param_expressions;

	Token line;

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

#define initExpression(_expression) {\
\
	initToken((_expression).tokens.expression);\
	initToken((_expression).tokens.name);\
\
	initFlag((_expression).flags.optional);\
	initFlag((_expression).flags.strict);\
\
}

#define initLine(_line) {\
\
	initExpression((_line).single_expression);\
	(_line).param_expressions = NULL;\
\
	initToken((_line).line);\
\
	initOther((_line).other);\
\
	(_line).action = ACTION_NONE;\
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

#define resetExpression(_expression) {\
\
	resetToken((_expression).tokens.expression);\
	resetToken((_expression).tokens.name);\
\
	resetFlag((_expression).flags.optional);\
	resetFlag((_expression).flags.strict);\
\
}

#define resetLine(_line) {\
\
	resetExpression((_line).single_expression);\
	if ((_line).param_expressions) {\
		listClear(*(_line).param_expressions);\
	}\
\
	initToken((_line).line);\
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

#define freeExpression(_expression) {\
	freeToken((_expression).tokens.expression);\
	freeToken((_expression).tokens.name);\
}

#define freeLine(_line) {\
	freeExpression((_line).single_expression);\
	if ((_line).param_expressions) {\
		listFree(*(_line).param_expressions);\
		free((_line).param_expressions);\
		(_line).param_expressions = NULL;\
	}\
	freeToken((_line).line);\
}

#define tokenExists(token) ((token).start && (token).end)

#define baseTokensExist(_line) (\
	(_line).single_expression.tokens.name.end && \
	(_line).single_expression.tokens.expression.end && \
	(_line).single_expression.tokens.expression.start\
)

#define verifyAction(_line) {\
	if (!((_line).has_expressions && baseTokensExist(_line))) {\
		(_line).action = ACTION_NONE;\
	}\
}

#define computeOther(_line) {\
	(_line).other.left.start = (_line).line.start;\
	(_line).other.left.length = (_line).single_expression.tokens.expression.start - (_line).line.start;\
	(_line).other.right.start = (_line).single_expression.tokens.expression.end;\
	(_line).other.right.length = (_line).line.end - (_line).single_expression.tokens.expression.end;\
}

#define computeTokenLength(token) {\
	if ((token).start && (token).end) {\
		(token).length = (token).end - (token).start;\
	} else {\
		(token).length = 0;\
	}\
}

#define computeLineTokensLengths(_line) {\
	computeTokenLength((_line).line);\
}

#define computeExpressionTokensLengths(_expression) {\
	computeTokenLength((_expression).tokens.name);\
	computeTokenLength((_expression).tokens.expression);\
}

#define printToken(_token, _name, _prefix) printf(_prefix "token \"" _name "\": (%p, %zu, %p, %p)\n", (_token).start, (_token).length, (_token).end, (_token).copy);

#define printFlag(_flag, _name, _prefix) printf(_prefix "flag \"" _name "\": (%s)\n", (_flag) ? "true" : "false");

#define printOther(_other, _name, _prefix) printf(_prefix "other_" _name ": (%p, %zu)\n", (_other).start, (_other).length);

#define printAction(_action, _prefix) printf(_prefix "action %s\n", (_action == ACTION_PARAM) ? "ACTION_PARAM" : (_action == ACTION_REF) ? "ACTION_REF" : "ACTION_NONE");

#define printExpression(_expression, _name, _prefix) {\
\
	printf(_prefix "expression \"" _name "\":\n");\
\
	printToken((_expression).tokens.expression, "expression", "\t\t");\
	printToken((_expression).tokens.name, "name", "\t\t");\
\
	printFlag((_expression).flags.optional, "optional", "\t\t");\
	printFlag((_expression).flags.strict, "strict", "\t\t");\
\
}

#define printLine(_line) {\
	printf("line %p\n", &(_line));\
	printAction((_line).action, "\t");\
	printToken((_line).line, "line", "\t");\
	printOther((_line).other.left, "left", "\t");\
	printExpression((_line).single_expression, "single_expression", "\t");\
	printOther((_line).other.right, "right", "\t");\
}