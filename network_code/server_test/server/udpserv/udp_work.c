#include "allnet.h"
#define MAXDATASIZE 100

void udp_work(int socketfd)
{	
	struct sockaddr_in cliaddr;
    socklen_t clilen;
    int num;
    char buf[MAXDATASIZE];
	clilen=sizeof(cliaddr);
    while(1)  
    {
       num =recvfrom(socketfd,buf,MAXDATASIZE,0,(struct sockaddr*)&cliaddr,&clilen);                                   
 
       if (num < 0)
    	{
       		perror("recvfrom() error\n");
       		exit(1);
    	}
 
       buf[num] = '\0';
       printf("You got a message (%s) from cliaddr.\nIt's ip is%s, port is %d.\n",buf,inet_ntoa(cliaddr.sin_addr),htons(cliaddr.sin_port)); 
       sendto(socketfd,"Welcometo my serveraddr.\n",22,0,(struct sockaddr *)&cliaddr,clilen);
       if(!strcmp(buf,"bye"))
       break;
    }
}