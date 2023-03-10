/*
--------------------------------------------------------------------------
xsh_ready - take a process into the ready state
--------------------------------------------------------------------------
*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


shellcmd xsh_psready(int nargs, char* args[])
{
	/*xsh_psready.c*/ 

	struct procent* prptr; /* pointer to process		*/
	int32 i;			   /* index into proctabl		*/
	char* pstate[] = {	   /* names for process states	*/
					  "free ", "curr ", "ready", "recv ", "sleep", "susp ",
					  "wait ", "rtime " };

	/* For argument '--help', emit help about the 'ps' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
	{
		printf("Use: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tDisplays information about running processes\n");
		printf("Options:\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}

	/* Check for valid number of arguments */

	if (nargs > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

	/* Print header for items from the process table */

	printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
		"Pid", "Name", "State", "Prio", "Ppid", "Stack Base",
		"Stack Ptr", "Stack Size");

	printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
		"---", "----------------", "-----", "----", "----",
		"----------", "----------", "----------");

	/* Output information for each process */

	for (i = 0; i < NPROC; i++)
	{
		prptr = &proctab[i];
		if (prptr->prstate != PR_READY)
		{
			continue;
		}
		printf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %10d\n",
			i, prptr->prname, pstate[(int)prptr->prstate],
			prptr->prprio, prptr->prparent, prptr->prstkbase,
			prptr->prstkptr, prptr->prstklen);
	}
	return 0;
}
