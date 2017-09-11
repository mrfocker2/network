#include "allnet.h"


#include "read.c"
#include "write.c"
#define	MAXN 16384		/* max # bytes client can request */
#define MAXLINE 1024

void web_child(int sockfd)
{
	int ntowrite;
	ssize_t	nread;
	char line[MAXLINE], result[MAXN];

	for ( ; ; ) 
	{
		if ((nread = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

			/* 4line from client specifies #bytes to write back */
		ntowrite = atol(line);
		if ((ntowrite <= 0) || (ntowrite > MAXN))
		{
			printf("client request for %d bytes", ntowrite);
			exit(0);
		}

		Writen(sockfd, result, ntowrite);
	}
}
