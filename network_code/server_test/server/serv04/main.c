#include "allnet.h"

void *thread_func(void *arg);

int main(int argc, const char *argv[])
{   
    struct sockaddr_in *cliaddr;
    bzero(cliaddr, 0);
    int len = sizeof(cliaddr);
    int listenfd = tcp_pre(argv[1], argv[2]);
    signal(SIGCHLD, resource_getback);
    while(1)
    {
    	int peerfd = serv_accept(listenfd, len, cliaddr);
    	pthread_t tid;
    	pthreads_create(&tid, NULL, &thread_func, (void*)peerfd);
    }
    close(listenfd);
    return 0;
}


