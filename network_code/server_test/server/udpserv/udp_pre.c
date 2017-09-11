#include "allnet.h"

int udp_pre(const char* servaddr, const char* port)
{
	int sockfd;
    struct sockaddr_in serveraddr;
 
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
    {
       printf("create socket wrong.");
       exit(1);
    }
 
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = ntohs(atoi(port));
    serveraddr.sin_addr.s_addr = inet_addr(servaddr);
    if(bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
       printf("bind wrong.");
       exit(1);
    }   
	return sockfd;
}

