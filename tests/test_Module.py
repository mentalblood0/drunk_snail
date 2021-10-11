from broker_tester import Module



c = Module('10.8.5.170', '8002')


def test_basic():

    result = c.sessions_get()

    assert type(result) == list