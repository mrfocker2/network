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



ssize_t	writen(int fd, const void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) 
        {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) 
		{
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}

void Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
		printf("writen error");
}
