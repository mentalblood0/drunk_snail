import uuid
import pytest

from drunk_snail_python import addTemplate, removeTemplate, render



@pytest.fixture
def param_values():
	return [str(i) for i in range(100)]


def render_lambda(text, params={}, refs={}):

	for name, text in (refs | {'l': text}).items():
		try:
			removeTemplate(name)
		except NameError:
			pass
		addTemplate(name, text)

	return render('l', params)