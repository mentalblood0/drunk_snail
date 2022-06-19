import pytest
from drunk_snail import Template



@pytest.fixture
def one_param_template():
	return '<!-- (param)x -->'


def test_equality(one_param_template):

	t1 = Template('test_sugar_equality_1', one_param_template)
	t2 = Template('test_sugar_equality_2', one_param_template)

	assert t1 == t2


def test_length(one_param_template):
	assert len(Template('test_sugar_length', one_param_template)) == len(one_param_template)