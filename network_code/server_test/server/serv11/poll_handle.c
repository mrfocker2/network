#include "allnet.h"

//void poll_add_fd(poll_p *p, int fd);
//void poll_del_fd(poll_p *p, int i);

void poll_pre(poll_p *p, int listenfd){
    p->listenfd = listenfd;
    int i;
    for(i = 0; i < 1024; i++){
       p->pclients[i].fd = -1;
    }
    p->pclients[0].fd = listenfd;
    p->pclients[0].events = POLLIN;
    p->maxi = 0;
    p->nready = 0;
}

void poll_do_wait(poll_p *p){
    int nready;
    do{
        nready = poll(p->pclients, p->maxi + 1, -1);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
    {
        printf("poll wait wrong\n");
        exit(1);
    }
    p->nready = nready;
}



/*void poll_handle_data(poll_p *p){
    if(p->nready == 0)
        return;
    int i;
    char recvbuf[1024] = {0};
    for(i = 1; i <= p->maxi; i++){
        int peerfd = p->pclients[i].fd;
        if(peerfd == -1)
            continue;
        if(p->pclients[i].revents & POLLIN){
            int ret = Readline(peerfd, recvbuf, 1024);
            if(ret == -1)
            {
                printf("read wrong\n");
                exit(1);
            }
            else if(ret == 0){
                printf("client closed\n");
                poll_del_fd(p, i);
                continue;
            }
            Writen(peerfd, recvbuf, atol(recvbuf));
        }
    }
}*/

void poll_handle_accept(poll_p *p, struct sockaddr_in *cliaddr, socklen_t *clilen)
{
    if(p->pclients[0].revents & POLLIN){
        int peerfd = accept(p->listenfd, (struct sockaddr*)&cliaddr, clilen);
        if(peerfd == -1)
        {
            printf("accept wrong\n");
            exit(1);
        }
        poll_add_fd(p, peerfd);
        --p->nready;
    }
}

void poll_add_fd(poll_p *p, int fd){
    int i;
    for(i = 0; i < 1024; i++){
        if(p->pclients[i].fd == -1){
            p->pclients[i].fd = fd;
            p->pclients[i].events= POLLIN;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    }
    if(i == 1024){
        fprintf(stderr, "too many pclients\n");
        close(fd);
        exit(1);
    }
}

void poll_del_fd(poll_p *p, int i){
    assert(i >= 1 && i < 1024);//
    close(p->pclients[i].fd);
    p->pclients[i].fd = -1;
}

void poll_close(poll_p *p)
{
    close(p->listenfd);
}