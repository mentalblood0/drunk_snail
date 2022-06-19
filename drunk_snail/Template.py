from __future__ import annotations

import pydantic
import dataclasses
from typing import Any

import drunk_snail_c



@pydantic.dataclasses.dataclass(
	config=type('Config', tuple(), {'arbitrary_types_allowed': True}),
	frozen=True
)
class Template:

	name: str
	_text: dataclasses.InitVar[str] = None

	def __post_init__(self, _text):
		if type(_text) == str:
			drunk_snail_c.addTemplate(self.name, _text)

	@property
	def text(self) -> str:
		return drunk_snail_c.getTemplate(self.name)

	def __call__(self, parameters: dict = None) -> str:
		return drunk_snail_c.render(self.name, parameters or {})

	def __repr__(self) -> str:
		return f"(name='{self.name}', source={self.source})"
	
	def __str__(self) -> str:
		return self.text

	def __len__(self) -> int:
		return len(self.text)

	def __eq__(self, other: Any) -> bool:
		return (
			isinstance(other, self.__class__)
			and (hash(self) == hash(other))
		)

	def __hash__(self) -> int:
		return hash(self.text)