from broker_tester import Client



c = Client('10.8.5.170', '8003')


def test_basic():

    result = c.sessions_post('test_session')

    assert type(result) == dict and 'id' in result