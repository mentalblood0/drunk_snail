import sys
import json

from .. import Template, default_keywords



description = 'Render template to stdout or to file'

args = [
	(str,	None,	'-I',	'--input',			True,	'Path to template file',											None),
	(str,	None,	'-a',	'--args',			False,	'Arguments for template in JSON format (string or path to file)',	None),
	(str,	'+',	'-d',	'--dependencies',	False,	'Paths to files that may be use by ref operator in compiling',		None),
	(str,	None,	'-O',	'--output',			False,	'Path to output file',												None),
	(str,	None,	'-o',	'--open_tag',		False,	'Keyword for open tag',												None),
	(str,	None,	'-c',	'--close_tag',		False,	'Keyword for close tag',											None),
	(str,	None,	'-p',	'--param_operator',	False,	'Keyword for param operator',										None),
	(str,	None,	'-r',	'--ref_operator',	False,	'Keyword for reference operator',									None),
	(str,	None,	'-n',	'--line_break',		False,	'Keyword for line break',											None)
]


def handler(args):

	try:
		with open(args.input) as f:
			template_text = f.read()
	except FileNotFoundError:
		print(f"File not found: {args.input}")
		return 1

	try:
		json.loads(args.args)
	except json.decoder.JSONDecodeError:
		try:
			with open(args.args) as f:
				try:
					args = json.load(f)
				except json.decoder.JSONDecodeError as e:
					print(f"Can not parse file {args.args} as JSON: {e}")
					return 3
		except FileNotFoundError:
			print(f"Can not parse {args.args} as JSON, can not load file {args.args}")
			return 2

	keywords = {
		name: getattr(args, name) or default_keywords[name]
		for name in default_keywords
	}

	result = Template('_temp', template_text, keywords)()

	if args.output:
		try:
			with open(args.output, 'w') as f:
				f.write(result)
		except FileNotFoundError:
			print(f"Can not open file for writing: {args.output}")
	else:
		sys.stdout.write(result)
	
	return 0