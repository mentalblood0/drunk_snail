from . import compileTemplates

import argparse



parser = argparse.ArgumentParser(description='Compile templates')

for e in [
	('-i',	'--input_dir',			False, 'Path to templates directory',			'templates'			),
	('-o',	'--output_dir',			False, 'Path to output directory',				'compiled_templates'),
	('-ot',	'--open_tag',			False, 'String treated as open tag',			'<--'				),
	('-ct',	'--close_tag',			False, 'String treated as close tag',			'-->'				),
	('-po',	'--param_operator',		False, 'String treated as param operator',		'(param)'			),
	('-ro', '--ref_operator',		False, 'String treated as reference operator',	'(ref)'				),
	('-oo',	'--optional_operator',	False, 'String treated as optional operator',	'(optional)'		),
]:
	parser.add_argument(
	e[0],			e[1],		required=e[2],			help=e[3],						default=e[4],
		type=str,
	)

args = parser.parse_args()
args_dict = {
	name: getattr(args, name)
	for name in dir(args) if not name.startswith('_')
}


compileTemplates(**args_dict, log=0)