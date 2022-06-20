import uuid

from drunk_snail_c import addTemplate, render



def render_lambda(text, params={}, used_names={}):

	while (name := uuid.uuid4().hex) in used_names:
		pass
	used_names[name] = True

	addTemplate(name, text)
	return render(name, params)