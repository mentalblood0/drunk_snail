from timeit import timeit

from drunk_snail import Template
from drunk_snail.sources import StringSource



if __name__ == '__main__':

	approach = [
		'append',
		'comprehension',
		'comprehension'
	][2]

	keywords = {
		'open_tag': '<!--',
		'close_tag': '-->',
		'param_operator': '(param)',
		'ref_operator': '(ref)'
	}
	template_name_prefix = "t"

	folding_depth = 15
	experiments_number = 1000

	t = [
		Template(
			f'{template_name_prefix}0',
			StringSource(f"{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"),
			keywords,
			approach=approach
		),
		Template(
			f'{template_name_prefix}1',
			StringSource(f"{keywords['open_tag']} {keywords['ref_operator']}{template_name_prefix}0 {keywords['close_tag']}\n{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
			keywords,
			approach=approach
		)
	]

	for i in range(2, folding_depth):
		t.append(
			Template(
				f'{template_name_prefix}{i}',
				StringSource(f"{keywords['open_tag']} {keywords['ref_operator']}{template_name_prefix}{i-2} {keywords['close_tag']}\n{keywords['open_tag']} {keywords['ref_operator']}{template_name_prefix}{i-1} {keywords['close_tag']}\n{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
				keywords,
				approach=approach
			)
		)
	
	templates_must_be_parsed = [
		[t[0]],
		[t[1], t[0]]
	]
	for i in range(2, folding_depth):
		templates_must_be_parsed.append([
			t[i],
			*templates_must_be_parsed[i-1],
			*templates_must_be_parsed[i-2]
		])
	characters_must_be_parsed = sum(len(t) for t in templates_must_be_parsed[-1])

	overall_time = 0
	for i in range(experiments_number):
		t[-1]._actual_template._compiled = None
		t[-1]._actual_template._function = None
		overall_time += timeit([
			't[-1].compiled',
			't[-1].function'
		][0], globals=globals(), number=1)

	f_size = len(t[-1].compiled)
	f_lines_number = t[-1].compiled.count('\n') + 1
	mean_time = overall_time / experiments_number

	input_speed = characters_must_be_parsed / mean_time / 1024 / 1024
	output_speed = f_size / mean_time / 1024 / 1024

	print(f"Experiments number: {experiments_number}")
	print(f"Overall time: {overall_time}s")
	print(f"Mean time: {mean_time}s")
	print(f"Resulted function size: {f_size} characters in {f_lines_number} lines")
	print(f"Compilation speed: {round(input_speed)}MB/s -> {round(output_speed)}MB/s")