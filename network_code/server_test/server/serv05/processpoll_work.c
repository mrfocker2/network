#include "allnet.h"

pid_t process_poll_create(int i, int listenfd, int addrlen)
{
	pid_t	pid;
	void child_main(int, int, int);
	if ((pid = fork()) > 0)
		return(pid);
			
	child_main(i, listenfd, addrlen);	
}

void child_main(int i, int listenfd, int addrlen)
{
	int connfd;
	socklen_t clilen;
	struct sockaddr	*cliaddr;

	cliaddr = (struct sockaddr*)malloc(addrlen);

	printf("child %d starting\n", i);
	for ( ; ; ) 
	{
		clilen = addrlen;
		connfd = accept(listenfd, cliaddr, &clilen);
		server_work(connfd);		/* process the request */
		close(connfd);
	}
}