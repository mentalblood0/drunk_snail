typedef struct KeywordData {
	char *keyword;
	char *last_inclusion;
	int length;
	char last_symbol;
} KeywordData;


typedef struct Keywords {
	Tree *tree;
	KeywordData **data;
} Keywords;


Keywords* createKeywords(int number_of_keywords) {

	Keywords *result = malloc(sizeof(Keywords));
	result->tree = createTree();
	
	result->data = calloc(number_of_keywords, sizeof(KeywordData*));

	return result;

}


void addKeywordByKeywords(Keywords *keywords, char *keyword, char symbol) {

	char *value_to_insert = malloc(sizeof(char) * 2);
	value_to_insert[0] = symbol;
	value_to_insert[1] = 0;
	treeInsert(keywords->tree, keyword, value_to_insert);

	KeywordData *data = malloc(sizeof(KeywordData));
	data->last_inclusion = NULL;

	char *k = keyword;
	for (; *k; k++);
	data->length = (int)(k - keyword);
	data->last_symbol = *k;

	data->keyword = malloc(sizeof(char) * (data->length + 1));
	strncpy(data->keyword, keyword, (data->length + 1));

	keywords->data[(int)symbol] = data;

}