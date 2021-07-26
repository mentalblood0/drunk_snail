from .common import *

import os
import argparse



parser = argparse.ArgumentParser(description='Compile and manage templates')

subparsers = parser.add_subparsers(title='subcommands')


main_module_name = os.path.basename(os.path.dirname(__file__))
subcommands_list = [
	'compile'
]
for c in subcommands_list:
	command_module = importlib.import_module(f'{main_module_name}.subcommands.{c}')
	command_parser = subparsers.add_parser(c, description=command_module.description)
	command_parser.set_defaults(handle=command_module.handle)
	for a in command_module.args:
		short_name = a[0]
		long_name = a[1]
		try:
			choices = a[5]
		except:
			choices = None
		command_parser.add_argument(
			short_name,
			long_name,
			required=a[2],
			help=a[3],
			default=a[4],
			type=str,
			choices=choices
		)

args = parser.parse_args()

args.handle(args)