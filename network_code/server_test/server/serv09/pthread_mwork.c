#include "allnet.h"
#include "pthread_pollm.h"


void thread_make(int i)
{
	void *thread_main(void *);

	pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *) i);
	return;		/* main thread returns */
}

void *thread_main(void *arg)
{
	int connfd,peerfd;
	void server_work(int);

	printf("thread %d starting\n", (int) arg);
	for ( ; ; ) 
	{
    	lock(&clifd_mutex);
		peerfd = w_wait(connfd);
		unlock(&clifd_mutex);
		tptr[(int) arg].thread_count++;
		server_work(peerfd);		/* process request */
		close(peerfd);
	}
}
