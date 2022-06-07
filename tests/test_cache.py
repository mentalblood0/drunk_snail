import pytest

from drunk_snail import Template
from drunk_snail.sources import StringSource, FileSource



def test_no_cacheSetup():

	with pytest.raises(Exception):
		assert Template(
			'test_cache_no_cacheSetup',
			StringSource('<!-- (param)x -->')
		)(
			{'x': 'lalala'},
			use_cache = True
		) == 'lalala'


def test_basic():

	t = Template(
		'test_cache_basic',
		StringSource('<!-- (param)x -->')
	)
	t.setupCache({
		('x',)
	})

	for x in ['lalala', 'lololo']:
		assert t(
			{'x': x},
			use_cache = True
		) == x

	assert len(t._cache.values) == 1


def test_list():

	t = Template(
		'test_cache_long_path',
		StringSource('<!-- (param)x -->')
	)
	t.setupCache({
		('x',)
	})

	for x in [['l', 'a'], ['l', 'o']]:
		assert t(
			{'x': x},
			use_cache = True
		) == '\n'.join(x)

	assert len(t._cache.values) == 1