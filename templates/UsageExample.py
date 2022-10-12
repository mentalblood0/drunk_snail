from drunk_snail import Template


Template('Row').register(
'''<!-- (param)row_template -->'''
)
table = Template('Table')
table.register(
'''<!-- (param)table_template -->'''
)

args = <!-- (param)table_arguments -->

result = table(args)
assert result == b'''<!-- (param)table_result -->'''