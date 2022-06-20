import uuid
import pytest

from drunk_snail_c import addTemplate, render



@pytest.fixture
def param_values():
	return [str(i) for i in range(100)]


def render_lambda(text, params={}, used_names={}):

	while (name := uuid.uuid4().hex) in used_names:
		pass
	used_names[name] = True

	addTemplate(name, text)
	return render(name, params)