import pytest
import pydantic
from drunk_snail import Template
from drunk_snail.sources import StringSource



s = '<!-- (param)x -->'


def test_equality():
	
	t1 = Template('test_sugar_equality_1', StringSource(s))
	t2 = Template('test_sugar_equality_2', StringSource(s))

	assert t1 == t2


def test_length():

	t = Template('test_sugar_length', StringSource(s))
	
	assert len(t) == len(s)


def test_dir():
	
	t = Template('test_sugar_dir', StringSource(s))

	for name in dir(t):
		assert name.startswith('__') or not name.startswith('_')