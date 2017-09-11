#include "allnet.h"

int serv_accept(int listenfd, socklen_t len, struct sockaddr_in *cliaddr)
{
	int connfd;
    if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len)) <= 0)
        {
        	printf("accpet wrong\n");
        	exit(1);
        }
    return connfd;
}