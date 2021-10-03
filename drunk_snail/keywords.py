class Keyword:

	def __init__(self, value, symbol):
		self.value = value
		self.symbol = symbol


#defaults

syntax = {
	'open_tag':				Keyword('<!--', 'o'),
	'close_tag':			Keyword('-->', 'c'),
	'param_operator':		Keyword('(param)', 'p'),
	'ref_operator':			Keyword('(ref)', 'r'),
	'optional_operator':	Keyword('(optional)', '?'),
	'line_break':			Keyword('\n', 'n')
}

default_keywords = {
	name: keyword.value
	for name, keyword in syntax.items()
}