#include	"allnet.h"
#include	"pthread_pollm.h"

pthread_mutex_t	mlock;
pid_t	child_make(int i, int listenfd, int addrlen)
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

	cliaddr = malloc(addrlen);

	printf("child %ld starting\n", (long) getpid());
	for ( ; ; ) {
		clilen = addrlen;
		/*lock(&clifd_mutex);
		connfd = accept(listenfd, cliaddr, &clilen);
		unlock(&clifd_mutex);*/
		connfd = pthread_lock_accept(&mlock, listenfd, cliaddr, &clilen);

		web_child(connfd);		/* process the request */
		close(connfd);
	}
}
