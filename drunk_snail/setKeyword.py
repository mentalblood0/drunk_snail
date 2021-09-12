from drunk_snail_c import addKeyword as _addKeyword, removeKeyword as _removeKeyword



class Keyword:

	def __init__(self, value, symbol):
		self.value = value
		self.symbol = symbol


syntax = {
	'open_tag':				Keyword('<!--', 'o'),
	'close_tag':			Keyword('-->', 'c'),
	'param_operator':		Keyword('(param)', 'p'),
	'ref_operator':			Keyword('(ref)', 'r'),
	'optional_operator':	Keyword('(optional)', '?')
}


def setKeyword(type, keyword):

	if not type in syntax:
		return False

	old_value = syntax[type].value
	syntax[type].value = keyword

	_removeKeyword(old_value)
	_addKeyword(syntax[type].value, syntax[type].symbol)

	return True


import sys
sys.modules[__name__] = setKeyword