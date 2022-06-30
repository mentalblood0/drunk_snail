#include "../include/getTemplate.h"

#include "../include/Template.h"
#include "../include/templates.h"

#include "../modules/prefix_tree/include/prefix_tree.h"



getTemplate_result getTemplate(char *name) {

	getTemplate_result result;
	result.text = NULL;
	result.length = 0;

	Template *template = dictionaryLookup(templates, name);
	if (template == NULL) {
		return result;
	}

	result.text = template->text;
	result.length = template->length;

	return result;

}