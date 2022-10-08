import drunk_snail_python



class Template:

	def __init__(self, name: str):
		self.name = name

	@property
	def text(self) -> str:
		return drunk_snail_python.getTemplate(self.name)

	def register(self, text: str) -> None:
		drunk_snail_python.removeTemplate(self.name)
		drunk_snail_python.addTemplate(self.name, text)

	def unregister(self) -> None:
		drunk_snail_python.removeTemplate(self.name)

	def __call__(self, parameters: dict = None) -> str:
		return drunk_snail_python.render(self.name, parameters or {})