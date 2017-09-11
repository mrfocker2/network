#include "allnet.h"

static int nchildren;
static pid_t *pids;
pid_t process_poll_create(int, int, int);

int main(int argc, char *argv[])
{
	void sig_int(int);
	
	int i;
	socklen_t addrlen;
	int listenfd = tcp_pre(argv[1], argv[2]);
	nchildren = atoi(argv[argc - 1]);
	pids = (pid_t*)calloc(nchildren, sizeof(pid_t));
	signal(SIGINT, sig_int);
	for (i = 0; i < nchildren; i++)
	{
		pids[i] = process_poll_create(i, listenfd, addrlen);
		
	}
	signal(SIGINT, sig_int);
	for ( ; ; )
		pause();	/* everything done by children */
}

void sig_int(int signo)
{
	poll_resource_back(nchildren, pids);
	exit(0);
}
