#include "allnet.h"

int main(int argc, char* argv[])
{
    int socketfd = udpclient_connect(argc, argv[1]);
    udpclient_work(socketfd, argv[1], argv[2], argv[3]);
    close(socketfd);
}
