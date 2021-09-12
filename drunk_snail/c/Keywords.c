typedef struct KeywordData {
	char *last_inclusion;
	int length;
	char last_symbol;
} KeywordData;


typedef struct Keywords {
	Tree *tree;
	KeywordData **data;
} Keywords;


Keywords* createKeywordsData(int number_of_keywords) {

	Keywords *result = malloc(sizeof(Keywords));
	result->tree = createTree();
	result->data = calloc(number_of_keywords, sizeof(KeywordData*));

	return result;

}


Keywords *_keywords;