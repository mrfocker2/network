#include "allnet.h"

void select_handle_data(select_s *s){
    if(s->nready == 0)
        return;
    int i;
    char recvbuf[1024];
    for(i = 0; i < FD_SETSIZE; i++){
        if(s->clients[i] == -1)
           continue;
        int fd = s->clients[i];
        if(FD_ISSET(s->clients[i], &s->rset))
        { 
            int ret = Readline(fd, recvbuf, 1024);
            if(ret == -1)
            {
                printf("readline wrong\n");
                exit(1);
            }
            else if(ret == 0){
                printf("client closed\n");
                select_del_fd(s, i);
                continue;
            }
            Writen(fd, recvbuf, atol(recvbuf));
        }
    }
}