rd /s /q dist drunk_snail\drunk_snail.egg-info
py -m build -n && ^
pip install --force-reinstall dist\drunk_snail-1.6-cp39-cp39-win_amd64.whl
rem py setup.py install