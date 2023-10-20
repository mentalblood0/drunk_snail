import re
import typing
import functools
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

	@functools.cached_property
	def specified(self):
		return self

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

	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template']):
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
	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template']):
		match (result := parameters[self.name.value]):
			case str():
				yield result
			case list():
				for r in result:
					match r:
						case str():
							yield r
						case _:
							raise ValueError
			case _:
				raise ValueError

@dataclasses.dataclass(frozen = True, kw_only = False)
class Reference(Expression):
	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template']) -> typing.Generator[str, typing.Any, typing.Any]:
		match (inner := parameters[self.name.value]):
			case str():
				raise ValueError
			case list():
				for p in inner:
					match p:
						case str():
							raise ValueError
						case _:
							yield templates[self.name.value].rendered(p, templates)
			case _:
				yield templates[self.name.value].rendered(inner, templates)


@dataclasses.dataclass(frozen = True, kw_only = False)
class Line(Pattern):

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

	def _rendered(self, inner: tuple[str]):
		current = iter(inner)
		for _e in Expression.highlighted(self):
			match (e := _e.specified):
				case Other():
					yield e.value
				case Parameter() | Reference():
					yield next(current)

	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template']):
		return Delimiter.expression.pattern.join(
			''.join(self._rendered(inner))
			for inner in zip(
				*(
					p.specified.rendered(parameters, templates)
					for p in Expression.extracted(self)
				)
			)
		)

@dataclasses.dataclass(frozen = True, kw_only = False)
class Empty(Line):
	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template']):
		return self.value


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

	def rendered(self, parameters: 'Template.Parameters', templates: dict[str, 'Template']):
		return Delimiter.expression.pattern.join(
			l.rendered(parameters, templates)
			for l in self.lines
		)


print(
	Template(
		'<table>\n'
		'    <!-- (ref)Row -->\n'
		'</table>'
	).rendered({
		'Row': [
			{
				'cell1': ['1', '2'],
				'cell2': ['3', '4']
			},
			{
				'cell1': ['5', '6'],
				'cell2': ['7', '8']
			}
		]
	}, {
		'Row': Template(
			'<tr>\n'
			'    <td><!-- (param)cell1 --></td><td><!-- (param)cell2 --></td>\n'
			'</tr>'
		)
	})
)