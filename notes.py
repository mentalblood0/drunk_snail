def render_comprehension(Table):
	return ''.join([
		'<table>\n',
		''.join([
			''.join([
				'    <tr>\n',
				''.join([
					f'        <td>{cell}</td>\n'
					for cell in Row['cell']
				]),
				'    </tr>\n'
			])
			for Row in Table['Row']
		]),
		'</table>\n'
	])


def render(Root):
	return ''.join([

		# content
		'content\n',

		# start <!-- (param)name --> end
		''.join([
			f'start {name} end\n'
			for name in Root['name']
		]),

		# start <!-- (ref)Name --> end
		''.join([
			# Name processing result
			for Name in Root['Name']
		]),

	])