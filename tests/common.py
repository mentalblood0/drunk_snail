import uuid
import pytest

from drunk_snail_c import addTemplate, removeTemplate, render



@pytest.fixture
def param_values():
	return [str(i) for i in range(100)]


def render_lambda(text, params={}):

	try:
		removeTemplate('lambda')
	except NameError:
		pass
	addTemplate('lambda', text)

	return render('lambda', params)