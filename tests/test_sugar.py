import pytest
from drunk_snail import Template



@pytest.fixture
def one_param_template():
	return '<!-- (param)x -->'


def test_equality(one_param_template):

	t1 = Template('test_sugar_equality_1')
	t1.register(one_param_template)

	t2 = Template('test_sugar_equality_2')
	t2.register(one_param_template)

	assert t1 == t2


def test_length(one_param_template):

	t = Template('test_sugar_length')
	t.register(one_param_template)

	assert len(t) == len(one_param_template)