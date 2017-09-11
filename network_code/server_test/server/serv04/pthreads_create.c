#include "allnet.h"

void pthreads_create(pthread_t *tid, const pthread_attr_t *attr, void * (*func)(void *), void *arg)
{
	int n;
    if ( (n = pthread_create(tid, attr, func, arg)) == 0)
		return;
	else
		printf("pthread_create error");
}