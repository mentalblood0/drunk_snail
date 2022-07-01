#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#include "../include/Line.h"
#include "../include/parse.h"
#include "../include/Template.h"
#include "../include/templates.h"

#include "../modules/List/include/List.h"
#include "../modules/memoma/include/memoma.h"
#include "../modules/prefix_tree/include/prefix_tree.h"



parse_result addTemplate(char *name, char *text) {

	parse_result result;
	result.code = 0;
	result.message = NULL;

	Template *template;
	drunk_malloc_one(template, sizeof(Template), result.code);
	if (result.code) {
		return result;
	}

	size_t text_length = strlen(text) + 1;
	drunk_malloc_one(template->text, sizeof(char) * text_length, result.code);
	if (result.code) {
		free(template);
		return result;
	}
	memcpy_s(template->text, text_length, text, text_length);

	template->length = text_length - 1;
	template->buffer_size = template->length;
	listCreate(template->lines, Line, 16, result.code);
	if (result.code) {
		free(template->text);
		free(template);
		return result;
	}

	result.code = treeInsert(templates, name, template);
	if (result.code) {
		listClear(template->lines);
		free(template->text);
		free(template);
		return result;
	}

	return parse(name);

}