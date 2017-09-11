#include	"allnet.h"

static int		nchildren;
static pid_t	*pids;
static pthread_mutex_t	*mptr;

int
main(int argc, char **argv)
{
	int			listenfd, i;
	socklen_t	addrlen;
	void		sig_int(int);
	pid_t		child_make(int, int, int);

	listenfd = tcp_pre(argv[1], argv[2]);
	nchildren = atoi(argv[argc-1]);
	pids = calloc(nchildren, sizeof(pid_t));

	my_pthreadlock_init(NULL, mptr);
	for (i = 0; i < nchildren; i++)
		pids[i] = child_make(i, listenfd, addrlen);	/* parent returns */

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
	exit(0);
}
