from __future__ import annotations

import drunk_snail_c



class Template:

	name: str

	def register(self, text: str) -> None:
		drunk_snail_c.addTemplate(self.name, text)

	def unregister(self) -> None:
		drunk_snail_c.removeTemplate(self.name)

	@property
	def text(self) -> str:
		return drunk_snail_c.getTemplate(self.name)

	def __str__(self) -> str:
		return self.text

	def __len__(self) -> int:
		return len(self.text)

	def __hash__(self) -> int:
		return hash(self.text)

	def __eq__(self, other: Template) -> bool:
		return hash(self) == hash(other)

	def __repr__(self) -> str:
		return f"(name='{self.name}', hash={hash(self)})"

	def __call__(self, parameters: dict = None) -> str:
		return drunk_snail_c.render(self.name, parameters or {})