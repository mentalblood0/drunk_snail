from types import ModuleType



def compilePythonFunction(text: str, name: str):

	compiled_function = compile(text, '', 'exec')
	temp_module = ModuleType('')
	exec(compiled_function, temp_module.__dict__)

	return getattr(temp_module, name)