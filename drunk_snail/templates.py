from .common import singleton



@singleton
class templates(dict):
    pass



import sys
sys.modules[__name__] = templates