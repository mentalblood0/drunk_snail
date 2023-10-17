import re
import typing
import functools
import itertools
import dataclasses



@dataclasses.dataclass(frozen = True, kw_only = False)
class Pattern:

	value      : str

	expression = re.compile('.*')

	def __post_init__(self):
		if not self.expression.fullmatch(self.value):
			raise ValueError(f'Expression {self.expression} does not match value {self.value}')

	@classmethod
	@property
	def pattern(cls):
		return cls.degrouped

	@classmethod
	@property
	def named(cls):
		return f'(?P<{cls.__name__}>{cls.degrouped})'

	@classmethod
	@property
	def optional(cls):
		return f'{cls.named}?'

	@classmethod
	@property
	@functools.cache
	def degrouped(cls):
		return re.sub(
			re.compile(r'\(\?P<\w+>([^\)]+)\)'),
			r'\1',
			cls.expression.pattern
		)

	@functools.cached_property
	def groups(self):
		if (match := self.expression.fullmatch(self.value)) is None:
			raise ValueError
		if not (result := match.groupdict()):
			raise ValueError
		return result

	@classmethod
	def extracted(cls, source: 'Pattern'):
		return (
			cls(source.value[m.start():m.end()])
			for m in cls.expression.finditer(source.value)
		)

	@classmethod
	def highlighted(cls, source: 'Pattern'):
		last = None
		for m in cls.expression.finditer(source.value):
			if (
				last is None and
				m.start() > (last_end := 0)
			) or (
				last is not None and
				m.start() > (last_end := last.end())
			):
				yield Other(source.value[last_end:m.start()])
			last = m
			yield cls(source.value[m.start():m.end()])
		if last is None:
			yield Other(source.value)
		else:
			if (last_end := last.end()) != len(source.value):
				yield Other(source.value[last_end:])


@dataclasses.dataclass(frozen = True, kw_only = False)
class Name(Pattern):
	expression = re.compile('\\w+')

@dataclasses.dataclass(frozen = True, kw_only = False)
class Spaces(Pattern):
	expression = re.compile(' *')

@dataclasses.dataclass(frozen = True, kw_only = False)
class Open(Pattern):
	expression = re.compile('<!--')

@dataclasses.dataclass(frozen = True, kw_only = False)
class Close(Pattern):
	expression = re.compile('-->')

@dataclasses.dataclass(frozen = True, kw_only = False)
class Delimiter(Pattern):
	expression = re.compile('\n')

@dataclasses.dataclass(frozen = True, kw_only = False)
class Other(Pattern):

	expression = re.compile('.*')

	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template'], left: str = '', right: str = ''):
		print(f'rendered {self}')
		return self.value


@dataclasses.dataclass(frozen = True, kw_only = False)
class Operator(Pattern):

	expression = re.compile(f'\\({Name.named}\\)')

	@functools.cached_property
	def name(self):
		return self.groups['Name']


@dataclasses.dataclass(frozen = True, kw_only = False)
class Optional(Operator):
	expression = re.compile(r'\(optional\)')


@dataclasses.dataclass(frozen = True, kw_only = False)
class Expression(Pattern):

	@dataclasses.dataclass(frozen = True, kw_only = False)
	class Type(Operator):

		class Parameter(Operator):
			expression = re.compile(r'\(param\)')

		class Reference(Operator):
			expression = re.compile(r'\(ref\)')

		@functools.cached_property
		def specified(self):
			for C in (Expression.Type.Parameter, Expression.Type.Reference):
				try:
					return C(self.value)
				except ValueError:
					continue
			raise ValueError

	class Name(Name):
		...

	expression = re.compile(Open.pattern + Spaces.pattern + Optional.optional + Type.named + Name.named + Spaces.pattern + Close.pattern)

	@functools.cached_property
	def type(self):
		return Expression.Type(self.groups['Type']).specified

	@functools.cached_property
	def name(self):
		return Expression.Name(self.groups['Name'])

	@functools.cached_property
	def specified(self):
		match self.type:
			case Expression.Type.Parameter():
				return Parameter(self.value)
			case Expression.Type.Reference():
				return Reference(self.value)

@dataclasses.dataclass(frozen = True, kw_only = False)
class Parameter(Expression):
	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template'], left: str = '', right: str = ''):
		print(f'rendered {self}')
		match (result := parameters[self.name.value]):
			case str() | list():
				return str(result)
			case _:
				raise ValueError

@dataclasses.dataclass(frozen = True, kw_only = False)
class Reference(Expression):
	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template'], left: str = '', right: str = '') -> str:
		print(f'rendered {self}, templates are {templates}, parameters are {parameters}')
		match (inner := parameters[self.name.value]):
			case str():
				raise ValueError
			case list():
				return Delimiter.expression.pattern.join(
					templates[self.name.value].rendered(p, templates, left, right)
					for p in inner
					if not isinstance(p, str)
				)
			case _:
				return templates[self.name.value].rendered(inner, templates, left, right)


@dataclasses.dataclass(frozen = True, kw_only = False)
class Line(Pattern):

	@dataclasses.dataclass(frozen = True, kw_only = False)
	class WithParameters(Pattern):
		...

	@dataclasses.dataclass(frozen = True, kw_only = False)
	class WithReferences(Pattern):
		...

	@dataclasses.dataclass(frozen = True, kw_only = False)
	class Empty(Pattern):
		def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template'], left: str = '', right: str = ''):
			return self.value

	@functools.cached_property
	def specified(self):
		parameters = any(
			isinstance(e, Parameter)
			for e in self.parsed
		)
		references = any(
			isinstance(e, Reference)
			for e in self.parsed
		)
		if parameters and references:
			raise ValueError
		if parameters:
			return Line.WithParameters(self.value)
		if references:
			return Line.WithReferences(self.value)
		return Line.Empty(self.value)

	@property
	def expressions(self):
		return (
			e.specified
			for e in Expression.extracted(self)
		)

	@property
	def parsed(self):
		return (
			e.specified if isinstance(e, Expression) else e
			for e in Expression.highlighted(self)
		)

	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template'], left: str = '', right: str = '') -> str:
		print(f'rendered {self} -> {[*self.parsed]}')
		return ''.join(
			o.rendered(parameters, templates, left, right)
			for o in self.parsed
		)


@dataclasses.dataclass(frozen = True, kw_only = False)
class Template(Pattern):

	Parameters = dict[str, typing.Union[str, list[typing.Union[str, 'Parameters']], 'Parameters']]

	expression = re.compile('(?:.*\n)*(?:.*)?')

	@property
	def lines(self):
		return (
			Line(l)
			for l in self.value.split(Delimiter.expression.pattern)
		)

	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template'], left: str = '', right: str = ''):
		return Delimiter.expression.pattern.join(
			l.rendered(parameters, templates, left, right)
			for l in self.lines
		)


template = Template('<!-- (param)parameter -->\nstart<!-- (param)p1 -->after p1<!-- (param)p2 -->end')
print(
	template.rendered({
		'parameter' : 'value',
		'p1'        : 'v1',
		'p2'        : 'v2'
	}, {})
)

row = Template(
'''<tr>
    <td><!-- (param)cell --></td>
</tr>'''
)
table = Template(
'''<table>
    <!-- (ref)Row -->
</table>'''
)

print(
	table.rendered({
		"Row": [
			{
				"cell": [
					"1",
					"2"
				]
			},
			{
				"cell": [
					"3",
					"4"
				]
			}
		]
	}, {
		'Row': row
	})
)