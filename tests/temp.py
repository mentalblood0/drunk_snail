# all lines exclude last (currently just all):

for p in ([None] if ((not P) or (not 'p' in P)) else (P['p'] if type(P['p']) == list else [P['p']])):
	result += f'''	<x-:IgnoreComments>{p}</x-:IgnoreComments>\n'''



# last line:

if (not P) or (not 'p' in P):
    result += f'''	<x-:IgnoreComments></x-:IgnoreComments>'''
elif type(P['p']) != list:
    result += f'''	<x-:IgnoreComments>{P['p']}</x-:IgnoreComments>'''
else:
    for p in P['p']:
	    result += f'''	<x-:IgnoreComments>{p}</x-:IgnoreComments>\n'''

# ... but what if the last line in current template not the last line in root template ?