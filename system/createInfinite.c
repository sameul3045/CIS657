/*CreateInfinite.c - create and resume an infinite process with a
priority.*/
#include <xinu.h>
void infinite(void);
void createInfinite(
	pri16 prio // new process priority
) {
	pid32 pid = create(infinite, 1024, prio, "New Process", 0);
	kprintf("\npid: %d\n", pid);
	resume(pid);
}
void infinite(void) {
	while (TRUE);
}