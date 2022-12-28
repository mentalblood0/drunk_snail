import pytest



@pytest.fixture
def table_width() -> int:
	return 100


@pytest.fixture
def table_height() -> int:
	return 100