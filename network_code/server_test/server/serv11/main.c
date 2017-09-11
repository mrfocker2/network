#include "allnet.h"

int main(int argc, const char *argv[])
{
    int listenfd = tcp_pre(argv[1], argv[2]);
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    poll_p p;
    poll_pre(&p, listenfd);
    while(1){
        poll_do_wait(&p);
        poll_handle_accept(&p, &cliaddr, &clilen);
        poll_handle_data(&p);
    }
    poll_close(&p);
    return 0;
}