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



parse_result addTemplate(char *name, char *text, size_t text_length) {

	parse_result result;
	result.code = 0;
	result.message = NULL;

	Template *template;
	drunk_malloc_one(template, sizeof(Template), result.code);
	if (result.code) {
		return result;
	}

	drunk_malloc_one(template->text, sizeof(char) * (text_length + 1), result.code);
	if (result.code) {
		free(template);
		return result;
	}
	memcpy(template->text, text, text_length + 1);

	template->length = text_length;
	template->buffer_size = text_length;
	listCreate(template->lines, Line, text_length / 16 + 1, result.code);
	if (result.code) {
		free(template->text);
		free(template);
		return result;
	}

	result.code = treeInsert(templates, name, template);
	if (result.code) {
		listFree(template->lines);
		free(template->text);
		free(template);
		return result;
	}

	return parse(name);

}