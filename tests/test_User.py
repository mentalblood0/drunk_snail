from broker_tester import User



def test_basic():

    u = User('10.8.5.170', '8002')

    assert type(u.get('/sessions', 200)) == list


def test_post():

    u = User('10.8.5.170', '8003')
    result = u.post('/sessions', 200, {'name': 'test_session'})

    assert type(result) == dict and 'id' in result