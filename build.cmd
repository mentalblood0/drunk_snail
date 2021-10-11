rd /s /q -rf dist broker_tester\broker_tester.egg-info
py -m build -n
py -m pip install --force-reinstall dist\broker_tester-0.1.0-py3-none-any.whl