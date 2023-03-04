#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void waiter(
	pri16 priority /* Priority value for this process */
)
{
	printf("Wait priority & pid: [%d,%d]\n", priority, getpid());

	while (TRUE)
	{
		// do nothing at this time.
	}
}