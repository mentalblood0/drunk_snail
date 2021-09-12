char *open_last = keywords->data[(int)'o']->last_inclusion;
// ------------------ BEFORE ------------------
char *prev_line_break = keywords->data[(int)'n']->last_inclusion;
char *line_before_open_tag_start = prev_line_break;
char *line_before_open_tag_end = open_last-1;
if (line_before_open_tag_start <= line_before_open_tag_end) {
	// ------------------ AFTER ------------------
	KeywordData *close_data = keywords->data[(int)'c'];
	char *close_last = close_data->last_inclusion;
	char *line_after_close_tag_start = close_last + close_data->length-1;
	char *line_after_close_tag_end = (*(c - 1) == '\n') ? c - 1 : c;
	// ------------------ PARAM ------------------
	KeywordData *param_data = keywords->data[(int)'p'];
	char *param_last = param_data->last_inclusion;
	if (param_last) {
		char *param_name_start = param_last + param_data->length;
		char *param_name_end = param_name_start;
		for (; *param_name_end != ' '; param_name_end++);

		if (optional) {
			addTabs(&result_end, tabs_number);
			compile__cpy_if(param_name_start, param_name_end);
			tabs_number++;
		}
		addTabs(&result_end, tabs_number);
		compile__cpy_for(param_name_start, param_name_end);
		addTabs(&result_end, tabs_number);
		compile__cpy_one('\t');
		compile__cpy_print_left_part();
		addTabs(&result_end, inner_tabs_number);
		if (prefix_start)
			compile__memcpy(prefix_start, prefix_end);
		compile__memcpy(line_before_open_tag_start, line_before_open_tag_end);
		compile__cpy_one('{');
		compile__memcpy(param_name_start, param_name_end);
		compile__cpy_one('}');
		compile__memcpy(line_after_close_tag_start, line_after_close_tag_end);
		if (postfix_start)
			compile__memcpy(postfix_start, postfix_end);
		compile__cpy_one('\\');
		compile__cpy_one('n');
		compile__cpy_print_right_part();
		if (optional)
			tabs_number--;
	}
	// ------------------ REF ------------------
	KeywordData *ref_data = keywords->data[(int)'r'];
	char *ref_last = ref_data->last_inclusion;
	if (ref_last) {
		char *ref_name_start = ref_last + ref_data->length;
		char *ref_name_end = ref_name_start;
		for (; *ref_name_end != ' '; ref_name_end++);

		char temp = *ref_name_end;
		*ref_name_end = 0;
		// compile__cpy_for(ref_name_start, ref_name_end);
		keywords->data[(int)'p']->last_inclusion = NULL;
		keywords->data[(int)'r']->last_inclusion = NULL;
		char *subtemplate_prefix_start = line_before_open_tag_start;
		// for (; *subtemplate_prefix_start == '\t'; subtemplate_prefix_start++);
		if (subtemplate_prefix_start != line_before_open_tag_start)
			subtemplate_prefix_start--;
		if (optional) {
			addTabs(&result_end, tabs_number);
			compile__cpy_if(ref_name_start, ref_name_end);
			tabs_number++;
		}
		char *subtemplate_text = compile_(
			ref_name_start,
			keywords,
			templates_tree,
			depth,
			subtemplate_prefix_start,
			line_before_open_tag_end,
			line_after_close_tag_start,
			line_after_close_tag_end,
			tabs_number + 1,
			depth + 1,
			log
		);
		*ref_name_end = temp;
		addTabs(&result_end, tabs_number);
		compile__cpy_for(ref_name_start, ref_name_end);
		compile__memcpy(subtemplate_text, subtemplate_text + strlen(subtemplate_text));
		if (optional)
			tabs_number--;
	}
}
tag_on_this_line = 0;