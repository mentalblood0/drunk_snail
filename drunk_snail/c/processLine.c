char *break_ = keywords->data[(int)'n']->last_inclusion; 
char *open_ = keywords->data[(int)'o']->last_inclusion;
char *close_ = keywords->data[(int)'c']->last_inclusion;
char *param_ = keywords->data[(int)'p']->last_inclusion;
char *ref_ = keywords->data[(int)'r']->last_inclusion;
if (
	open_ && close_ &&
	(
		(param_ && (param_ > open_) && (param_ < close_)) ||
		(ref_ && (ref_ > open_) && (ref_ < close_))
	)
) {
	fprintf(stderr, "processLineWithTag\n");
	#include "processLineWithTag.c"
} else {
	#include "processLineWithoutTag.c"
}