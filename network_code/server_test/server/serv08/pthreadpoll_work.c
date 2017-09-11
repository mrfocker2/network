#include "allnet.h"
#include "pthread_polle.h"

pthread_mutex_t	mlock;

void thread_main(void *arg)
{
	int connfd;
	socklen_t clilen, addrlen;
	struct sockaddr	*cliaddr;
	cliaddr = malloc(addrlen);
	printf("thread %d starting\n", (int) arg);

	for ( ; ; ) 
	{
		clilen = addrlen;
		connfd = pthread_lock_accept(&mlock, listenfd, cliaddr, &clilen);
		server_work(connfd);		/* process request */
		close(connfd);
	}
}


