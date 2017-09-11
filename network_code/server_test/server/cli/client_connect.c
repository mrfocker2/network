#include "allnet.h"

int client_connect(int argc, char *servaddr, char *PORT)
{
    int  sockfd;
    struct sockaddr_in server;
    if (argc!=3)
    {
       printf("Usage:%s <IP Address>\n",servaddr);
       exit(1);
    }
    if((gethostbyname(servaddr))==NULL)
    {
       printf("gethostname wrong\n");
       exit(1);
    }
    if((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
       printf("create socket wrong\n");
       exit(1);
    }
    bzero(&server,sizeof(server));
    server.sin_family= AF_INET;
    server.sin_port = ntohs(atoi(PORT));
    inet_pton(AF_INET, servaddr, &server.sin_addr);
    if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1)
    {
       printf("connect server wrong\n");
       exit(1);
    }
    return sockfd;
}