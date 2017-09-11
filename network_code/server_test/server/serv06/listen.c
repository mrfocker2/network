#include <sys/time.h>	
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>	/* inet(3) functions */
#include <errno.h>
#include <fcntl.h>	/* for nonblocking */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>	/* for S_xxx file mode constants */
#include <sys/uio.h>	/* for iovec{} and readv/writev */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>	/* for Unix domain sockets */
#include <sys/select.h>	/* for convenience */
#include <sys/param.h>	/* OpenBSD prereq for sysctl.h */
#include <sys/sysctl.h>
#include <poll.h>	/* for convenience */
#include <strings.h>	/* for convenience */
#include <sys/ioctl.h>
#include <pthread.h>
#define	LISTENQ	 1024	/* 2nd argument to listen() */
#define	MAXLINE	 4096	/* max text line length */
#define	BUFFSIZE 8192	/* buffer size for reads and writes */



int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	int listenfd, n;
	const int on = 1;
	struct addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
	{
		printf("tcp_listen error for %s, %s: %s",
				 host, serv, gai_strerror(n));
		exit(0);
	}
	ressave = res;

	do {
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (listenfd < 0)
			continue;		/* error, try next one */

		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;			/* success */

		close(listenfd);	/* bind error, close and try next one */
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL)	/* errno from final socket() or bind() */
		printf("tcp_listen error for %s, %s", host, serv);

	listen(listenfd, LISTENQ);

	if (addrlenp)
		*addrlenp = res->ai_addrlen;	/* return size of protocol address */

	freeaddrinfo(ressave);

	return(listenfd);
}

int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	return(tcp_listen(host, serv, addrlenp));
}
