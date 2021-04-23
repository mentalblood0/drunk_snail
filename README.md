# drunk snail

Template engine

* Has two implementations: C and Python
* Compiles templates to Python functions

About syntax:

* All is text
* Except what is bounded by xml comment parentheses
* You can set your own bounding
* `<!-- (ref)AnotherTemplateName -->` includes template(s) with name "AnotherTemplateName"
* `<!-- (param)some_param_name -->` includes param value(s)

About resulted Python function parameters:

* It is a dictionary
* Values might be lists (try or see test result)
* Key-Value might be name and value of `param`(s)
* Key-Value might be name and parameters of `ref`(s)

Tests are provided