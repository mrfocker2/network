#include	"allnet.h"

static int		nchildren;
static pid_t	*pids;
long			*cptr, *meter(int);	/* for counting #clients/child */

int
main(int argc, char **argv)
{
	int			listenfd, i;
	socklen_t	addrlen;
	void		sig_int(int);
	pid_t		process_poll_create(int, int, int);
	
	listenfd = tcp_pre(argv[1], argv[2]);
	nchildren = atoi(argv[argc-1]);
	pids = calloc(nchildren, sizeof(pid_t));
	cptr = meter(nchildren);

	my_filelock_init("/tmp/lock.XXXXXX");	/* one lock file for all children */
	for (i = 0; i < nchildren; i++)
		pids[i] = process_poll_create(i, listenfd, addrlen);	/* parent returns */

	signal(SIGINT, sig_int);

	for ( ; ; )
		pause();	/* everything done by children */
}

void
sig_int(int signo)
{
	int		i;
	void	pr_cpu_time(void);

		/* terminate all children */
	for (i = 0; i < nchildren; i++)
		kill(pids[i], SIGTERM);
	while (wait(NULL) > 0)		/* wait for all children */
		;
	if (errno != ECHILD)
	{
		printf("wait error");
		exit(1);
	}

	pr_cpu_time();

	for (i = 0; i < nchildren; i++)
		printf("child %d, %ld connections\n", i, cptr[i]);

	exit(0);
}
