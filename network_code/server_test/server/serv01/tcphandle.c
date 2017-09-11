/**
 * @file 	tcphandle.c
 * @brief	from create socket to listen
 *
 * @author	leon
 * @email	924704739@qq.com
 */
#include "allnet.h"

 int tcphandle(char *host)
 {
    struct sockaddr_in serveraddr;
    int sockfd;
    int ret = 0;
	int opt = 1;
    //create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
    if(-1 == sockfd)
    {
       printf("create socket error\n");
    }
        
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = ntohs(atoi(host));
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind
    ret = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(-1 == ret)
    {
        printf("bind error\n");
    //listen
    }
    ret = listen(sockfd,128);
    if(-1 == ret)
    {
       printf("listen error\n");
    }

    return sockfd;
 }