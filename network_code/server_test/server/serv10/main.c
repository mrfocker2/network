#include "allnet.h"

int main(int argc, const char *argv[])
{   
    void select_handle_data(select_s *);
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    select_s s;
    int listenfd = tcp_pre(argv[1], argv[2]);
    select_pre(&s, listenfd);
    
    while(1){
        select_do_wait(&s);
        select_handle_accept(&s, &cliaddr, &clilen);
        select_handle_data(&s);
    }
    close(listenfd);
    return 0;
}