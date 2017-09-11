#include "allnet.h"
#include "pthread_polle.h"

void pthread_poll_create(Thread *tptr, int nthreads, void*(*thread_main)(void *))
{
	int i;
	
	for (i = 0; i < nthreads; i++)
		{
			pthread_create(&tptr[i].thread_tid, NULL, thread_main, (void *) i);		
		}
}
