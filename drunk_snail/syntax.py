from .Keyword import Keyword



syntax = {
	'open_tag':				Keyword('<!--', 'o'),
	'close_tag':			Keyword('-->', 'c'),
	'param_operator':		Keyword('(param)', 'p'),
	'ref_operator':			Keyword('(ref)', 'r'),
	'optional_operator':	Keyword('(optional)', '?'),
	'line_break':			Keyword('\n', 'n')
}