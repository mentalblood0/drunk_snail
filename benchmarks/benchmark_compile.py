from timeit import timeit

from drunk_snail import Template
from drunk_snail.sources import StringSource



keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'ref_operator': '~'
}

t = [
	Template(
		f'benchmark_compile_0', 
		StringSource('( $x )'), 
		keywords
	),
	Template(
		f'benchmark_compile_1', 
		StringSource('( ~benchmark_compile_0 )\n( $x )'), 
		keywords
	)
]
folding_depth = 15

for i in range(2, folding_depth):
	t.append(
		Template(
			f'benchmark_compile_{i}', 
			StringSource(f'( ~benchmark_compile_{i-2} )\n( ~benchmark_compile_{i-1} )\n( $x )'), 
			keywords
		)
	)

experiments_number = 10000
overall_time = 0

for i in range(experiments_number):
	t[-1]._actual_template._compiled = None
	overall_time += timeit('t[-1].compiled', globals=globals(), number=1)

lines_number = t[-1].compiled.count('\n')

print(f"Experiments number: {experiments_number}")
print(f"Overall time: {overall_time}")
print(f"Mean time: {overall_time / experiments_number}")
print(f"Resulted function size: {len(t[-1].compiled)} characters in {lines_number} lines")