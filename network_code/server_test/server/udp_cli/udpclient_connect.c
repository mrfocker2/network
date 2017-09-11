#include "allnet.h"

int udpclient_connect(int argc, char *servaddr)
{
    
    int sockfd;
 
    if (argc != 4)
    {
       printf("Usage: <./filename><IP Address><PORT><message>\n");
       exit(1);
    }

    if ((gethostbyname(servaddr))==NULL)
    {
       printf("gethostbyname()error\n");
       exit(1);
    }

    if ((sockfd=socket(AF_INET, SOCK_DGRAM,0))==-1)
    {
       printf("socket() error\n");
       exit(1);
    }

    return sockfd;
}
