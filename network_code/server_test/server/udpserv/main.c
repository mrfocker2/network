#include "allnet.h"

int main(int argc, char *argv[])
{   
	void udp_work(int);
    int socketfd = udp_pre(argv[1], argv[2]);
    udp_work(socketfd);
    close(socketfd);    
}