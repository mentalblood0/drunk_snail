from .syntax import syntax



default_keywords: dict[str, str] = {
	name: keyword.value
	for name, keyword in syntax.items()
}