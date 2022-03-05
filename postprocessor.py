import re
import argparse



parser = argparse.ArgumentParser(description='Compile prints to optimized form')
parser.add_argument(
	'--file',
	'-f',
	help='Path to file to compile',
	required=True
)
parser.add_argument(
	'--output',
	'-o',
	help='Path to output file',
	required=False
)



def removeLineComments(text):
	return re.sub(r'\n\/\*.*\*\/', '', text)




args = parser.parse_args()

with open(args.file, encoding='utf8') as f:
	text = f.read()

result = removeLineComments(text)

with open(args.output or 'a.out', 'w', encoding='utf8') as f:
	f.write(result)