/*xsh_wait.c - xsh_*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

shellcmd xsh_wait(int nargs, char* args[])
{
	pri16 priority = INITPRIO;

	// Output info for '--help' argument
	if (nargs == 2)
	{
		if (strncmp(args[1], "--help", 7) == 0)
		{
			printf("Usage: %s <priority>\n\n", args[0]);
			printf("Description:\n");
			printf("\tStarts a new process that runs forever with the given priority.\n");
			printf("Options:\n");
			printf("\t<priority>\tThe priority value to use when creating the forever\n");
			printf("\t\t\tprocess.  Valid values are in the range: 1 to 127.\n");
			printf("\t\t\tDefault value is 20.\n");
			printf("\t--help    \tDisplay this help and exit\n");
			return OK;
		} 

		if (is_positive_integer(args[1]) == TRUE)
		{
			priority = atoi(args[1]);

			// check to make sure the priority is valid.
			if (priority < 1 || priority > 127)
			{
				fprintf(stderr, "%s: Incorrect argument - value needs to be in the range of 1 to 127 inclusive.\n", args[0]);
				fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
				return SYSERR;
			}
		}
		else
		{
			fprintf(stderr, "%s: Incorrect argument - value is not a postive number\n", args[0]);
			return SYSERR;
		}
	}

	// Check argument count
	else if (nargs > 2)
	{
		fprintf(stderr, "%s: Incorrect number of arguments\n", args[0]);
		return SYSERR;

	}
	pid32 pid_waiter = create(waiter, 1024, priority, "waitinggggggg", 0);
	resume(pid_waiter);
	return 0;
}