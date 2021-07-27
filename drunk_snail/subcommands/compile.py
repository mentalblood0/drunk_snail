from drunk_snail import compileTemplates

description = 'Compile templates'

args = [
	('-i',	'--input_dir',			False, 'Path to templates directory',			'templates'			),
	('-o',	'--output_dir',			False, 'Path to output directory',				'compiled_templates'),
	('-ot',	'--open_tag',			False, 'String treated as open tag',			'<!--'				),
	('-ct',	'--close_tag',			False, 'String treated as close tag',			'-->'				),
	('-po',	'--param_operator',		False, 'String treated as param operator',		'(param)'			),
	('-ro', '--ref_operator',		False, 'String treated as reference operator',	'(ref)'				),
	('-oo',	'--optional_operator',	False, 'String treated as optional operator',	'(optional)'		),
]

def handle(args):

	args_dict = {
		name: getattr(args, name)
		for name in dir(args) 
		if not name.startswith('_') and not name == 'handle'
	}

	compileTemplates(**args_dict, log=0)