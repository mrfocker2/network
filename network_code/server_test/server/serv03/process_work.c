#include "allnet.h"

void process_handle_data(int listenfd, int peerfd, pid_t pid)
{
    pid = process_create();
    if(pid == 0)
    {
    	close(listenfd); 
    	server_work(peerfd);
    	exit(0);
	}
	close(peerfd);
}
