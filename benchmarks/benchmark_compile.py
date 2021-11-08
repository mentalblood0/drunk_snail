from timeit import timeit

from drunk_snail import Template
from drunk_snail.sources import StringSource



if __name__ == '__main__':
	keywords = {
		'open_tag': '<!--',
		'close_tag': '-->',
		'param_operator': '(param)',
		'ref_operator': '(ref)'
	}

	t = [
		Template(
			f'benchmark_compile_0', 
			StringSource(f"{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
			keywords
		),
		Template(
			f'benchmark_compile_1', 
			StringSource(f"{keywords['open_tag']} {keywords['ref_operator']}benchmark_compile_0 {keywords['close_tag']}\n{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
			keywords
		)
	]
	folding_depth = 15

	for i in range(2, folding_depth):
		t.append(
			Template(
				f'benchmark_compile_{i}', 
				StringSource(f"{keywords['open_tag']} {keywords['ref_operator']}benchmark_compile_{i-2} {keywords['close_tag']}\n{keywords['open_tag']} {keywords['ref_operator']}benchmark_compile_{i-1} {keywords['close_tag']}\n{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
				keywords
			)
		)

	experiments_number = 10000
	overall_time = 0

	for i in range(experiments_number):
		t[-1]._actual_template._compiled = None
		overall_time += timeit('t[-1].compiled', globals=globals(), number=1)

	f_size = len(t[-1].compiled)
	f_lines_number = t[-1].compiled.count('\n')
	mean_time = overall_time / experiments_number

	print(f"Experiments number: {experiments_number}")
	print(f"Overall time: {overall_time}s")
	print(f"Mean time: {mean_time}s")
	print(f"Resulted function size: {f_size} characters in {f_lines_number} lines")
	print(f"Compilation speed: {f_size / mean_time / 1024 / 1024} MB/s")