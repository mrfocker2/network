#include "allnet.h"

void select_pre(select_s *s, int listenfd)
{
    s->listenfd = listenfd;
    FD_ZERO(&s->allset);
    FD_ZERO(&s->rset);
    FD_SET(listenfd, &s->allset);
    int i;
    for(i = 0; i < FD_SETSIZE; i++){
        s->clients[i] = -1;
    }
    s->maxi = -1;
    s->maxfd = listenfd;
}

void select_do_wait(select_s *s){
    s->rset = s->allset;
    do{
        s->nready = select(s->maxfd + 1, &s->rset, NULL, NULL, NULL);
    }while(s->nready == -1 && errno == EINTR);
}

void select_handle_accept(select_s *s, struct sockaddr_in *cliaddr, socklen_t *clilen)
{
    if(FD_ISSET(s->listenfd, &s->rset))
    {
        int peerfd = accept(s->listenfd, (struct sockaddr*)&cliaddr, clilen);
        if(peerfd == -1)
        {
            printf("accept wrong\n");
            exit(1);
        }
        select_add_fd(s, peerfd);
    }
    s->nready--;
}

void select_add_fd(select_s *s, int fd)
{
    int i;
    for(i = 0; i < FD_SETSIZE; i++)
    {
        if(s->clients[i] == -1)
        {
            s->clients[i] = fd;
            if(i > s->maxi)
                s->maxi = i;
            break;
        }
    }
    if(i == FD_SETSIZE)
    {
        printf("too many clients\n");
        close(fd);
        exit(1);//!
    }
    FD_SET(fd, &s->allset);
    if(fd > s->maxfd)
        s->maxfd = fd;
}

void select_del_fd(select_s *s, int i)
{
    assert(i >= 0 && i < FD_SETSIZE); //!
    int fd = s->clients[i];
    s->clients[i] = -1;
    FD_CLR(fd, &s->allset);
    close(fd);
}

void select_close(select_s *s)
{
    close(s->listenfd);
}