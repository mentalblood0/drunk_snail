from functools import singledispatch

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


def setKeyword(template_name, type, keyword):

	if not type in syntax:
		return False

	old_value = syntax[type].value
	syntax[type].value = keyword

	_removeKeyword(template_name, old_value)
	_addKeyword(template_name, syntax[type].value, syntax[type].symbol)

	return True


@singledispatch
def setKeywords(arg, keywords):
	pass

@setKeywords.register
def _(arg: str, keywords):
	for type, keyword in keywords.items():
		setKeyword(arg, type, keyword)


@setKeywords.register
def _(arg: list, keywords):
	for template_name in arg:
		for type, keyword in keywords.items():
			setKeyword(template_name, type, keyword)


import sys
sys.modules[__name__] = setKeywords