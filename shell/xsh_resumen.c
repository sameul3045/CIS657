/*xsh_resumen.c - xsh_resumen */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern sid32 semm;

shellcmd xsh_resumen(int nargs, char* args[]) {
	pri16 priority;
	char ch;
	char* chprio;
	pid32 pid;
	if (nargs == 1) {
		priority = INITPRIO;
	}
	else if (nargs == 2) {
		chprio = args[1];
		ch = *chprio++;
		priority = 0;
		while (ch != NULLCH) {
			if ((ch < '0') || (ch > '9')) {
				kprintf("%s: non-digit in priority\n", args[1]);
				return 1;
			}
			priority = 10 * priority + (ch - '0');
			ch = *chprio++;
			resume(priority);
		}
		if (priority < (pri16)MINKEY) {
			kprintf("%s: invalid priorty\n", args[1]);
			return 1;
		}
	}
	else {
		kprintf("Too many arguments\n");
		return 1;
	}
	return 0;
}