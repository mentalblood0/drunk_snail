from timeit import timeit
from mako.template import Template



with open('templates/mako_template.html', 'r', encoding='utf8') as f:
	text = f.read()

mytemplate = Template(text)

args = {
	'rows': [[v for v in range(0,100)] for row in range(0,10000)]
}
result = timeit('mytemplate.render(**args)', globals=globals(), number=1)
print(result)