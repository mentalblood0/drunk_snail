// ------------------ BEFORE ------------------
char *prev_line_break = keywords->data[(int)'n']->last_inclusion;
char *line_before_open_tag_start = prev_line_break+1;
char *line_before_open_tag_end = open_;
if (line_before_open_tag_start <= line_before_open_tag_end) {
	// ------------------ AFTER ------------------
	KeywordData *close_data = keywords->data[(int)'c'];
	char *line_after_close_tag_start = close_ + close_data->length;
	char *line_after_close_tag_end = (*(c - 1) == '\n') ? c - 1 : c;
	// ------------------ PARAM ------------------
	if (param_) {

		char *param_name_start = param_ + keywords->data[(int)'p']->length;
		char *param_name_end = param_name_start;
		for (; *param_name_end != ' '; param_name_end++);

		compileComprehension__cpy_for_start_unpack();

		compile__cpy_one('f');
		compile__cpy_one('"');
		compile__addTabs(&result_end, inner_tabs_number);
		if (prefix_start)
			compile__memcpy(prefix_start, prefix_end);
		compile__memcpy(line_before_open_tag_start, line_before_open_tag_end);
		compile__cpy_one('{');
		compile__memcpy(param_name_start, param_name_end);
		compile__cpy_one('}');
		compile__memcpy(line_after_close_tag_start, line_after_close_tag_end);
		if (postfix_start)
			compile__memcpy(postfix_start, postfix_end);
		compile__cpy_one('"');

		if (optional) {
			compileComprehension__cpy_for_end_optional(param_name_start, param_name_end);
		}
		else {
			compileComprehension__cpy_for_end(param_name_start, param_name_end);
		}

		compile__cpy_one(']');
		compile__cpy_one(',');

	} else {
		// ------------------ REF ------------------
		if (ref_) {

			char *ref_name_start = ref_ + keywords->data[(int)'r']->length;
			char *ref_name_end = ref_name_start;
			for (; *ref_name_end != ' '; ref_name_end++);

			char *ref_name = malloc(sizeof(char) * (ref_name_end - ref_name_start + 1));
			memcpy(ref_name, ref_name_start, ref_name_end - ref_name_start);
			ref_name[ref_name_end - ref_name_start] = 0;

			if (!depth)
				addRef(template, ref_name, ref_name_end - ref_name_start);

			keywords->data[(int)'p']->last_inclusion = NULL;
			keywords->data[(int)'r']->last_inclusion = NULL;
			char *subtemplate_prefix_start = line_before_open_tag_start;
			if (subtemplate_prefix_start != line_before_open_tag_start)
				subtemplate_prefix_start--;
			compileComprehension__cpy_for_start_unpack();
			
			compileComprehension_(
				compilation_result,
				ref_name,
				templates_tree,
				&result_end,
				buffer_size - (result_end - result),
				depth,
				subtemplate_prefix_start,
				line_before_open_tag_end,
				line_after_close_tag_start,
				line_after_close_tag_end,
				tabs_number + 2,
				depth + 1
			);
			free(ref_name);

			if (optional) {
				compileComprehension__cpy_for_end_optional(ref_name_start, ref_name_end);
			}
			else {
				compileComprehension__cpy_for_end(ref_name_start, ref_name_end);
			}
			compile__cpy_one(']');
			compile__cpy_one(',');

			if (compilation_result->code != 0) {
				if (!depth) {
					free(result);
				}
				return;
			}
			if (optional)
				tabs_number--;
		
		}
	}
}