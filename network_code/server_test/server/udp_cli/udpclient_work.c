#include "allnet.h"
#define MAXDATASIZE 100 

void udpclient_work(int socketfd, char* servaddr, char* PORT, char* msg)
{
    int num;
    char buf[MAXDATASIZE];
    socklen_t  addrlen;
    struct sockaddr_in server,cliaddr;

    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = ntohs(atoi(PORT));
    inet_pton(AF_INET, servaddr, &server.sin_addr);
       
    sendto(socketfd, msg,strlen(msg),0,(struct sockaddr *)&server,sizeof(server));
    addrlen = sizeof(server);
    while (1)
    {
       if((num=recvfrom(socketfd,buf,MAXDATASIZE,0,(struct sockaddr *)&cliaddr,&addrlen))== -1)
       {
           printf("rec from server error\n");
           exit(1);
       }
           buf[num]='\0';
           printf("Server Message:%s\n",buf);
           break;
    }
}