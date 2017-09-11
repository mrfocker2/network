#include "allnet.h"

int main(int argc, char *argv[])
{	
    int connfd, listenfd;
	socklen_t clilen;
	struct sockaddr_in cliaddr;
	if (argc != 3) 
	{  
       printf("Usage: %s <ip> <port>\n", argv[0], argv[1]);  
       return -1;  
    }
    
	listenfd = tcp_pre(argv[1], argv[2]);

	while(1)
    {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) 
        {
            printf("accept error");
            exit(1);
        }
        printf("Yougot a connection from cient's ip is %s, prot is %d\n",inet_ntoa(cliaddr.sin_addr),htons(cliaddr.sin_port));  
        send(connfd,"Welcometo my server.\n",22,0);
        close(connfd); 
    }
}
