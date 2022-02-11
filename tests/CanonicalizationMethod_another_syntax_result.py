def render(CanonicalizationMethod):
	result = []
	result.append(f'''<xd:CanonicalizationMethod xd1:Algorithm="http://www.w3.org/2010/xml-c14n2">\n''')
	for ignore_comments in ([None] if ((not CanonicalizationMethod) or (not 'ignore_comments' in CanonicalizationMethod)) else (CanonicalizationMethod['ignore_comments'] if type(CanonicalizationMethod['ignore_comments']) == list else [CanonicalizationMethod['ignore_comments']])):
		result.append(f'''	<x-:IgnoreComments>{ignore_comments}</x-:IgnoreComments>\n''')
	for trim_text_nodes in ([None] if ((not CanonicalizationMethod) or (not 'trim_text_nodes' in CanonicalizationMethod)) else (CanonicalizationMethod['trim_text_nodes'] if type(CanonicalizationMethod['trim_text_nodes']) == list else [CanonicalizationMethod['trim_text_nodes']])):
		result.append(f'''	<x-:TrimTextNodes>{trim_text_nodes}</x-:TrimTextNodes>\n''')
	for prefix_rewrite in ([None] if ((not CanonicalizationMethod) or (not 'prefix_rewrite' in CanonicalizationMethod)) else (CanonicalizationMethod['prefix_rewrite'] if type(CanonicalizationMethod['prefix_rewrite']) == list else [CanonicalizationMethod['prefix_rewrite']])):
		result.append(f'''	<x-:PrefixRewrite>{prefix_rewrite}</x-:PrefixRewrite>\n''')
	result.append(f'''	<x-:QNameAware>\n''')
	result.append(f'''		<!--You have a CHOICE of the next 4 items at this level-->\n''')
	if CanonicalizationMethod and 'qname_aware_element' in CanonicalizationMethod:
		for qname_aware_element in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_element' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_element'] if type(CanonicalizationMethod['qname_aware_element']) == list else [CanonicalizationMethod['qname_aware_element']])):
			result.append(f'''		<x-:Element x-:Name="string" x-:NS="{qname_aware_element}"/>\n''')
	for qname_aware_xpath_element in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_xpath_element' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_xpath_element'] if type(CanonicalizationMethod['qname_aware_xpath_element']) == list else [CanonicalizationMethod['qname_aware_xpath_element']])):
		result.append(f'''		<x-:XPathElement x-:Name="string" x-:NS="{qname_aware_xpath_element}"/>\n''')
	if CanonicalizationMethod and 'qname_aware_qualified_attr' in CanonicalizationMethod:
		for qname_aware_qualified_attr in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_qualified_attr' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_qualified_attr'] if type(CanonicalizationMethod['qname_aware_qualified_attr']) == list else [CanonicalizationMethod['qname_aware_qualified_attr']])):
			result.append(f'''		<x-:QualifiedAttr x-:Name="string" x-:NS="{qname_aware_qualified_attr}"/>\n''')
	if CanonicalizationMethod and 'qname_aware_unqualified_attr' in CanonicalizationMethod:
		for qname_aware_unqualified_attr in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_unqualified_attr' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_unqualified_attr'] if type(CanonicalizationMethod['qname_aware_unqualified_attr']) == list else [CanonicalizationMethod['qname_aware_unqualified_attr']])):
			result.append(f'''		<x-:UnqualifiedAttr x-:Name="string" x-:ParentName="string" x-:ParentNS="{qname_aware_unqualified_attr}"/>\n''')
	result.append(f'''	</x-:QNameAware>\n''')
	result.append(f'''</xd:CanonicalizationMethod>''')
	return ''.join(result)
