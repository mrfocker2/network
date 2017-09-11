#include "allnet.h"
#define  MAXDATASIZE 100
 
int main(int argc, char *argv[])
{
    int num;
    char  buf[MAXDATASIZE];
    int socketfd = client_connect(argc, argv[1], argv[2]);
    if((num=recv(socketfd,buf,MAXDATASIZE,0)) == -1)
    {
       printf("recv wrong\n");
       exit(1);
    }
    buf[num-1]='\0';
    printf("Server Message: %s\n",buf);
    close(socketfd);
    return 0;
}
    