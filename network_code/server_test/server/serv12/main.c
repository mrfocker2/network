#include "allnet.h"

int main(int argc, const char *argv[])
{
    void epoll_handle(epoll_e *, struct sockaddr_in *cliaddr, socklen_t *clilen);
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    int listenfd = tcp_pre(argv[1], argv[2]);
    epoll_e e;
    epoll_pre(&e, listenfd);
    while(1){
        epoll_do_wait(&e);
        epoll_handle(&e, &cliaddr, &clilen);
    }
    epoll_close(&e);
    return 0;
}