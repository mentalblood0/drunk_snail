if (((int)(*c) >= 0) && n->children[(int)*c]) {
	n = n->children[(int)*c];
	++potential_keyword_length;
} else {
	n = &keywords->tree->root;
	if (((int)(*c) >= 0) && n->children[(int)*c])
		n = n->children[(int)*c];
	
	potential_keyword_length = 0;
}

	if (n->value) {

		if (((char*)n->value)[0] == '?')
			optional = 1;

		if (((char*)n->value)[0] == 'n') {
			
			#include "processLine.c"
			
			keywords->data[(int)'o']->last_inclusion = NULL;
			keywords->data[(int)'c']->last_inclusion = NULL;
			keywords->data[(int)'p']->last_inclusion = NULL;
			keywords->data[(int)'r']->last_inclusion = NULL;
			keywords->data[(int)'?']->last_inclusion = NULL;
			optional = 0;
		
		}

		KeywordData *current_keyword_data = keywords->data[(int)((char*)n->value)[0]];
		current_keyword_data->last_inclusion = c + 1 - current_keyword_data->length;

	}