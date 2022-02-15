char *prev_line_break = keywords->data[(int)'n']->last_inclusion;
char *line_start = prev_line_break+1;
char *line_end = (*(c - 1) == '\n') ? c - 1 : c;
compile__addTabs(&result_end, tabs_number + 1);
compile__cpy_one('"');
compile__addTabs(&result_end, inner_tabs_number);
if (prefix_start)
	compile__memcpy(prefix_start, prefix_end);
if (line_start <= line_end)
	compile__memcpy(line_start, line_end);
if (postfix_start)
	compile__memcpy(postfix_start, postfix_end);
compile__cpy_one('"');
compile__cpy_one(',');
compile__cpy_one('\n');