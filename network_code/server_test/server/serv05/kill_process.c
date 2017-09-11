#include "allnet.h"

void poll_resource_back(int nchildren, pid_t *pids)
{
	int i;
	for (i = 0; i < nchildren; i++)
		kill(pids[i], SIGTERM);
	while (wait(NULL) > 0)		/* wait for all children */
		;
	if (errno != ECHILD)
		printf("wait error");
}