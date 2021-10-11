rm -rf dist broker_tester/broker_tester.egg-info
python3.9 -m build -n
python3.9 -m pip install --force-reinstall dist/broker_tester-0.1.0-py3-none-any.whl