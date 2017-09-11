#include "allnet.h"

/*void poll_handle_accept(poll_p *p)
{
    if(p->pclients[0].revents & POLLIN){
        int peerfd = accept(p->listenfd, NULL, NULL);
        if(peerfd == -1)
        {
            printf("accept wrong\n");
            exit(1);
        }
        poll_add_fd(p, peerfd);
        --p->nready;
    }
}*/

void poll_handle_data(poll_p *p)
{
	void poll_del_fd(poll_p *, int);
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
}
