#include "allnet.h"
#include "pthread_polle.h"

int pthread_lock_accept(pthread_mutex_t *mutex, int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int connfd;
	pthread_mutex_lock(mutex);
	connfd = accept(sockfd, addr, addrlen);
	pthread_mutex_unlock(mutex);
	return connfd;
}

