def processIncludes(source_file_path):
	text = None
	with open(source_file_path) as f:
		text = f.read()
	result_lines = []
	for line in text.split('\n'):
		if line.replace(' ', '').startswith('#include"'):
			pass
		else:
			result_lines.append(line)
	return '\n'.join(result_lines)

result = processIncludes('drunk_snail/c/compileTemplates.c')
with open('processIndludesOutput.c', 'w') as f:
	f.write(result)