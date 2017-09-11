#include "allnet.h"
#define	MAXN 16384		/* max # bytes client can request */
#define MAXLINE  4096   /* max text line length */

void server_work(int connfd)
{
	int ntowrite;
	ssize_t	nread;
	char line[MAXLINE], result[MAXN];
	while(1)
	{
		if ((nread = Readline(connfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
			/* 4line from client specifies #bytes to write back */
		ntowrite = atol(line);
		if ((ntowrite <= 0) || (ntowrite > MAXN))
		{
			printf("client request for %d bytes\n", ntowrite);
			exit(0);
		}
		printf("server get data : %s", line);
		Writen(connfd, result, ntowrite);
	}
}