#include "allnet.h"

int main(int argc, const char *argv[])
{
	void process_handle_data(int, int, pid_t);
	struct sockaddr_in *cliaddr;
    pid_t pid;
	int clilen = sizeof(cliaddr);
    int listenfd = tcp_pre(argv[1], argv[2]);
    signal(SIGCHLD, resource_getback);
    while(1)
    {
    	int peerfd = serv_accept(listenfd, clilen, cliaddr);
    	process_handle_data(listenfd, peerfd, pid);
    }
    close(listenfd);
    return 0;
}