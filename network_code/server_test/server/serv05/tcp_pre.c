/**
 * @file 	tcp_pre.c
 * @brief	from create socket to listen
 *
 * @author	leon
 * @email	924704739@qq.com
 */
#include "allnet.h"

 int tcp_pre(const char* servaddr, const char* port)
 {
    struct sockaddr_in serveraddr;
    int sockfd;
    int ret = 0;
	int opt = 1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
    if(-1 == sockfd)
    {
       printf("create socket error\n");
       exit(1);
    }
        
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = ntohs(atoi(port));
    serveraddr.sin_addr.s_addr = inet_addr(servaddr);

    ret = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(-1 == ret)
    {
        printf("bind error\n");
        exit(1);
    }
    ret = listen(sockfd,128);
    if(-1 == ret)
    {
       printf("listen error\n");
       exit(1);
    }

    return sockfd;
 }