#include	"allnet.h"

pid_t
process_poll_create(int i, int listenfd, int addrlen)
{
	pid_t	pid;
	void	child_main(int, int, int);

	if ( (pid = fork()) > 0)
		return(pid);		/* parent */

	child_main(i, listenfd, addrlen);	/* never returns */
}

void
child_main(int i, int listenfd, int addrlen)
{
	int				connfd;
	void			web_child(int);
	socklen_t		clilen;
	struct sockaddr	*cliaddr;
	extern long		*cptr;

	cliaddr = malloc(addrlen);

	printf("child %ld starting\n", (long) getpid());
	for ( ; ; ) {
		clilen = addrlen;
		my_lock_wait();
		connfd = accept(listenfd, cliaddr, &clilen);
		my_lock_release();
		cptr[i]++;

		web_child(connfd);		/* process the request */
		close(connfd);
	}
}
