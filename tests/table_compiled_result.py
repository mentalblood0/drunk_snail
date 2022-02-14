def render(Table):
	return ''.join([
		"<table>\n",
		''.join([
			''.join([
				"	<tr>\n",
				''.join([
					f"		<td>{cell}</td>\n"
					for cell in ([None] if ((not Row) or (not 'cell' in Row)) else (Row['cell'] if type(Row['cell']) == list else [Row['cell']]))
				]),
				"	</tr>\n",
			])
			for Row in ([None] if ((not Table) or (not 'Row' in Table)) else (Table['Row'] if type(Table['Row']) == list else [Table['Row']]))
		]),
		"</table>",
	])