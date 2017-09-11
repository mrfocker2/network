#include "allnet.h"
//#define MAXN 16384      /* max # bytes client can request */
#define MAXLINE  4096   /* max text line length */

//void epoll_handle_accept(epoll_e *e);
//void epoll_handle_data(epoll_e *e, int peerfd);
//void epoll_add_fd(epoll_e *e, int fd);
//void epoll_del_fd(epoll_e *e, int fd);

void epoll_pre(epoll_e *e, int listenfd)
{
    if((e->epollfd = epoll_create(1024)) == -1)
    {
        printf("epoll create wrong\n");
        exit(1);
    }
    e->listenfd = listenfd;
    epoll_add_fd(e, listenfd);
    e->nready = 0;
}

void epoll_do_wait(epoll_e *e)
{
    int nready;
    do{
        nready = epoll_wait(e->epollfd, e->events, 10242, -1);
    }while(nready == -1 && errno ==  EINTR);
    if(nready == -1)
       {
        printf("epoll wait wrong\n");
        exit(1);
    }
    e->nready = nready;
}

void epoll_handle_accept(epoll_e *e, struct sockaddr_in *cliaddr, socklen_t *clilen)
{
    int peerfd = accept(e->listenfd, (struct sockaddr*)&cliaddr, clilen);
    if(peerfd == -1)
    {
        printf("accept wrong\n");
        exit(1);
    }
    epoll_add_fd(e, peerfd);
}

void epoll_add_fd(epoll_e *e, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(epoll_ctl(e->epollfd, EPOLL_CTL_ADD, fd, &ev) == -1)
    {
        printf("ctl wrong\n");
        exit(1);
    }
}

void epoll_del_fd(epoll_e *e, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    if(epoll_ctl(e->epollfd, EPOLL_CTL_DEL, fd, &ev) == -1)
    {
        printf("del wrong\n");
        exit(1);
    }
}

void epoll_close(epoll_e *e)
{
    close(e->epollfd);
    close(e->listenfd);
}