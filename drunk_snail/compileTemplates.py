from compileTemplates import compileTemplates as compileTemplates_c


def compileTemplates(
	input_dir='templates', 
	output_dir='compiled_templates',
	open_tag='<!--',
	close_tag='-->',
	param_operator='(param)',
	ref_operator='(ref)',
	optional_operator='(optional)',
	log=0
):
	compileTemplates_c(
		input_dir,
		output_dir,
		open_tag,
		close_tag,
		param_operator,
		ref_operator,
		optional_operator,
		log
	)



import sys
sys.modules[__name__] = compileTemplates