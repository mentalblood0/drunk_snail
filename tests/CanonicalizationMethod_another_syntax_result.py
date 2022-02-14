def render(CanonicalizationMethod):
	return ''.join([
		"<xd:CanonicalizationMethod xd1:Algorithm="http://www.w3.org/2010/xml-c14n2">\n",
		''.join([
			f"	<x-:IgnoreComments>{ignore_comments}</x-:IgnoreComments>\n"
			for ignore_comments in ([None] if ((not CanonicalizationMethod) or (not 'ignore_comments' in CanonicalizationMethod)) else (CanonicalizationMethod['ignore_comments'] if type(CanonicalizationMethod['ignore_comments']) == list else [CanonicalizationMethod['ignore_comments']]))
		]),
		''.join([
			f"	<x-:TrimTextNodes>{trim_text_nodes}</x-:TrimTextNodes>\n"
			for trim_text_nodes in ([None] if ((not CanonicalizationMethod) or (not 'trim_text_nodes' in CanonicalizationMethod)) else (CanonicalizationMethod['trim_text_nodes'] if type(CanonicalizationMethod['trim_text_nodes']) == list else [CanonicalizationMethod['trim_text_nodes']]))
		]),
		''.join([
			f"	<x-:PrefixRewrite>{prefix_rewrite}</x-:PrefixRewrite>\n"
			for prefix_rewrite in ([None] if ((not CanonicalizationMethod) or (not 'prefix_rewrite' in CanonicalizationMethod)) else (CanonicalizationMethod['prefix_rewrite'] if type(CanonicalizationMethod['prefix_rewrite']) == list else [CanonicalizationMethod['prefix_rewrite']]))
		]),
		"	<x-:QNameAware>\n",
		"		<!--You have a CHOICE of the next 4 items at this level-->\n",
		''.join([
			f"		<x-:Element x-:Name="string" x-:NS="{qname_aware_element}"/>\n"
			for qname_aware_element in ([] if ((not CanonicalizationMethod) or (not 'qname_aware_element' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_element'] if type(CanonicalizationMethod['qname_aware_element']) == list else [CanonicalizationMethod['qname_aware_element']]))
		]),
		''.join([
			f"		<x-:XPathElement x-:Name="string" x-:NS="{qname_aware_xpath_element}"/>\n"
			for qname_aware_xpath_element in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_xpath_element' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_xpath_element'] if type(CanonicalizationMethod['qname_aware_xpath_element']) == list else [CanonicalizationMethod['qname_aware_xpath_element']]))
		]),
		''.join([
			f"		<x-:QualifiedAttr x-:Name="string" x-:NS="{qname_aware_qualified_attr}"/>\n"
			for qname_aware_qualified_attr in ([] if ((not CanonicalizationMethod) or (not 'qname_aware_qualified_attr' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_qualified_attr'] if type(CanonicalizationMethod['qname_aware_qualified_attr']) == list else [CanonicalizationMethod['qname_aware_qualified_attr']]))
		]),
		''.join([
			f"		<x-:UnqualifiedAttr x-:Name="string" x-:ParentName="string" x-:ParentNS="{qname_aware_unqualified_attr}"/>\n"
			for qname_aware_unqualified_attr in ([] if ((not CanonicalizationMethod) or (not 'qname_aware_unqualified_attr' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_unqualified_attr'] if type(CanonicalizationMethod['qname_aware_unqualified_attr']) == list else [CanonicalizationMethod['qname_aware_unqualified_attr']]))
		]),
		"	</x-:QNameAware>\n",
		"</xd:CanonicalizationMethod>",
	])