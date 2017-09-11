#include "allnet.h"
#include "pthread_polle.h"

int main(int argc, char *argv[])
{
	void thread_main(void *);
	listenfd = tcp_pre(argv[1], argv[2]);
	int nthreads = atoi(argv[argc - 1]);
	Thread *tptr;
	tptr = (Thread*)calloc(nthreads, sizeof(Thread));
	pthread_poll_create(tptr, nthreads, thread_main);   
	for ( ; ; )
		pause();	/* everything done by threads */
}
