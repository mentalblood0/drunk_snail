from drunk_snail import Template
from drunk_snail.sources import FileSource



def test_basic():
	assert Template('CanonicalizationMethod', FileSource('templates/CanonicalizationMethod.xml'))