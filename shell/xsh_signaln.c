/*xsh_signaln.c - xsh_signaln*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern sid32 gsem;

shellcmd xsh_signaln(int nargs, char* args[]) {
	int32 signalCount;
	char ch;
	char* chsig;
	if (nargs == 1) {
		signalCount = 1;
	}
	else if (nargs == 2) {
		chsig = args[1];
		ch = *chsig++;
		signalCount = 0;
		while (ch != NULLCH) {
			if ((ch < '0') || (ch > '9')) {
				kprintf("%s: non-digit in signal value\n", args[1]);
				return 1;
			}
			signalCount = 10 * signalCount + (ch - '0');
			ch = *chsig++;
		}
	}
	else {
		kprintf("Too Many arguments. \n");
		return 1;
	}
	signaln(gsem, signalCount);
	return 0;
}