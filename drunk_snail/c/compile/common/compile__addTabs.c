int compile__addTabs__i;
#define compile__addTabs(s_end, n) {\
	for (compile__addTabs__i = 0; compile__addTabs__i < n; compile__addTabs__i++) {\
		compile__cpy_one('\t');\
	}\
}