#include "allnet.h"

ssize_t process_create()
{
	pid_t pid;
    if((pid = fork()) < 0)
    {
    	printf("create process wrong");
    	exit(1);
    }
    return pid;
}