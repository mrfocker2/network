#include "allnet.h"

#define MAXLINE  4096   /* max text line length */

void epoll_handle(epoll_e *e, struct sockaddr_in *cliaddr, socklen_t *clilen)
{
	void epoll_handle_data(epoll_e *, int);
    int i;
    for(i = 0 ; i < e->nready; i++){
        int fd = e->events[i].data.fd;
        if(fd == e->listenfd){
            epoll_handle_accept(e, cliaddr, clilen);
        }
        else
            epoll_handle_data(e, fd);
    }
}

void epoll_handle_data(epoll_e *e, int peerfd)
{
    char recvbuf[MAXLINE];
    int ret = Readline(peerfd, recvbuf, MAXLINE);
    if(ret == -1)
    {
        printf("read wrong\n");
        exit(1);
    }
    else if(ret == 0){
        printf("client closed\n");
        epoll_del_fd(e, peerfd);
        return;
    }
    Writen(peerfd, recvbuf, atol(recvbuf));
}
