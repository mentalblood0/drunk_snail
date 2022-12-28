import json
import orjson
import pytest
import functools

from ..common import *



Args = dict[str, list[dict[str, list[str]]]]

@pytest.fixture
def args(table_width: int, table_height: int) -> Args:
	return {
		"Row": [
			{
				"cell": [
					str(x + y * table_width)
					for x in range(table_width)
				]
			}
			for y in range(table_height)
		]
	}


@pytest.mark.benchmark(group='serialize')
def test_args_to_str(benchmark, args: Args):
	benchmark(str, args)


@pytest.mark.benchmark(group='serialize')
def test_args_to_json(benchmark, args: Args):
	benchmark(json.dumps, args)


@pytest.mark.benchmark(group='serialize')
def test_args_to_json_with_indent(benchmark, args: Args):
	benchmark(functools.partial(json.dumps, indent=4), args)


@pytest.mark.benchmark(group='serialize')
def test_args_to_json_using_orjson(benchmark, args: Args):
	benchmark(orjson.dumps, args)