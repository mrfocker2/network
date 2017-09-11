#include "allnet.h"
#include "pthread_pollm.h"

int lock(pthread_mutex_t *clifd_mutex)
{
	return pthread_mutex_lock(clifd_mutex);
}

int unlock(pthread_mutex_t *clifd_mutex)
{
	return pthread_mutex_unlock(clifd_mutex);
}

void s_signal(int connfd)
{
	
	clifd[iput] = connfd;
	if (++iput == MAXNCLI)
		iput = 0;
	if (iput == iget)
		{
			printf("iput = iget = %d", iput);
			exit(0);
		}
	pthread_cond_signal(&clifd_cond);
}

int w_wait(int connfd)
{
	while (iget == iput)
		pthread_cond_wait(&clifd_cond, &clifd_mutex);
	connfd = clifd[iget];	/* connected socket to service */
	if (++iget == MAXNCLI)
		iget = 0;
	return connfd;
}


