import pytest
import pathlib



@pytest.fixture
def table_width() -> int:
	return 100


@pytest.fixture
def table_height() -> int:
	return 100


@pytest.fixture
def templates() -> pathlib.Path:
	return pathlib.Path(__file__).parent / 'templates'