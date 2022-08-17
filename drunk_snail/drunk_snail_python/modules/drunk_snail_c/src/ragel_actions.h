#define ragel_action_start_line line->line.start = p;

#define ragel_action_end_line {\
\
	line->line.end = p;\
\
	verifyAction(*line);\
	computeLineTokensLengths(*line);\
	computeOther(*line);\
\
	if (line->action == ACTION_NONE) {\
		if (\
			(template->lines.length >= 2) &&\
			(template->lines.start[template->lines.length - 2].action == ACTION_NONE)\
		) {\
			template->lines.start[template->lines.length - 2].line.length += 1 + line->line.length;\
			resetLine(*line);\
		} else {\
			allocNewLine(line, template->lines, alloc_error);\
		}\
	} else if (line->action == ACTION_PARAM_MULTI) {\
		if (line->param_expressions->start[line->param_expressions->length-1].tokens.name.copy == NULL) {\
			line->param_expressions->length -= 1;\
		}\
		allocNewLine(line, template->lines, alloc_error);\
	} else {\
		allocNewLine(line, template->lines, alloc_error);\
	}\
\
	current_expression = &line->single_expression;\
\
}

#define ragel_action_param line->action = ACTION_PARAM;
#define ragel_action_ref line->action = ACTION_REF;
#define ragel_action_optional current_expression->flags.optional = true;
#define ragel_action_strict current_expression->flags.strict = true;
#define ragel_action_start_name current_expression->tokens.name.start = p;
#define ragel_action_end_name current_expression->tokens.name.end = p;

#define ragel_action_start_expression {\
	if (!(current_expression->tokens.expression.start && current_expression->tokens.name.end))\
		current_expression->tokens.expression.start = p;\
}

#define ragel_action_end_expression {\
\
	current_expression->tokens.expression.end = p;\
\
	if (current_expression->tokens.name.start) {\
\
		computeExpressionTokensLengths(*current_expression);\
\
		drunk_malloc_one__parse(current_expression->tokens.name.copy, sizeof(char) * (current_expression->tokens.name.length + 1));\
		memcpy(current_expression->tokens.name.copy, current_expression->tokens.name.start, current_expression->tokens.name.length);\
		current_expression->tokens.name.copy[current_expression->tokens.name.length] = 0;\
\
	}\
\
	if (line->action == ACTION_PARAM) {\
\
		if (!line->param_expressions) {\
			line->param_expressions = malloc(sizeof(ExpressionList));\
			if (!line->param_expressions) {\
				exit__parse();\
			}\
			listCreate(*(line->param_expressions), Expression, 4, alloc_error);\
			if (alloc_error) {\
				exit__parse();\
			}\
			listExtend(*(line->param_expressions), Expression, alloc_error);\
			if (alloc_error) {\
				exit__parse();\
			}\
			line->param_expressions->start[0] = *current_expression;\
		} else {\
			if (line->param_expressions->length) {\
				line->action = ACTION_PARAM_MULTI;\
			}\
		}\
		listGetNew(*(line->param_expressions), Expression, current_expression, alloc_error);\
		if (alloc_error || !current_expression) {\
			exit__parse();\
		}\
		initExpression(*current_expression);\
\
	} else if (line->param_expressions) {\
		if (line->param_expressions->length) {\
			line->action = ACTION_NONE;\
		}\
	}\
\
}

#define ragel_action_end_expressions line->has_expressions = true;