#include "allnet.h"
#include "pthread_pollm.h"

static int nthreads;
int main(int argc, char **argv)
{
	int i, listenfd, connfd;
	void sig_int(int), thread_make(int);
	socklen_t addrlen, clilen;
	struct sockaddr	*cliaddr;

	listenfd = listenfd = tcp_pre(argv[1], argv[2]);
	
	cliaddr = (struct sockaddr*)malloc(addrlen);

	nthreads = atoi(argv[argc-1]);
	tptr = (Thread*)calloc(nthreads, sizeof(Thread));
	iget = iput = 0;

	for (i = 0; i < nthreads; i++)
		thread_make(i);		

	for ( ; ; ) 
	{
		clilen = addrlen;
		connfd = accept(listenfd, cliaddr, &clilen);
		lock(&clifd_mutex);
		s_signal(connfd);
		unlock(&clifd_mutex);
	}
}