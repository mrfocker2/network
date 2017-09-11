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


#include <sys/resource.h>

int getrusage(int, struct rusage *);
void pr_cpu_time(void)
{
	double	user, sys;
	struct rusage myusage, childusage;

	if (getrusage(RUSAGE_SELF, &myusage) < 0)
		printf("getrusage error");
	if (getrusage(RUSAGE_CHILDREN, &childusage) < 0)
		printf("getrusage error");

	user = (double) myusage.ru_utime.tv_sec +
					myusage.ru_utime.tv_usec/1000000.0;
	user += (double) childusage.ru_utime.tv_sec +
					 childusage.ru_utime.tv_usec/1000000.0;
	sys = (double) myusage.ru_stime.tv_sec +
				   myusage.ru_stime.tv_usec/1000000.0;
	sys += (double) childusage.ru_stime.tv_sec +
					childusage.ru_stime.tv_usec/1000000.0;

	printf("\nuser time = %g, sys time = %g\n", user, sys);
}
