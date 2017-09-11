/**
 * @file 	allnet.h
 * @brief	all header file
 *
 * @author	leon
 * @email	924704739@qq.com
 */

#ifndef	_ALLNET_H_
#define	_ALLNET_H_

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#if TIME_WITH_SYS_TIME
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#else
#if HAVE_SYS_TIME_H
#include	<sys/time.h>	/* includes <time.h> unsafely */
#else
#include	<time.h>		/* old system? */
#endif
#endif
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */

#ifdef	HAVE_SYS_SELECT_H
# include	<sys/select.h>	/* for convenience */
#endif

#ifdef	HAVE_SYS_SYSCTL_H
#ifdef	HAVE_SYS_PARAM_H
# include	<sys/param.h>	/* OpenBSD prereq for sysctl.h */
#endif
# include	<sys/sysctl.h>
#endif

#ifndef	HAVE_POLL_H
# include	<poll.h>		/* for convenience */
#endif

#ifndef	HAVE_SYS_EPOLL_H
# include	<sys/epoll.h>	/* for convenience */
#endif

#ifdef	HAVE_SYS_EVENT_H
# include	<sys/event.h>	/* for kqueue */
#endif

#ifdef	HAVE_STRINGS_H
# include	<strings.h>		/* for convenience */
#endif

/* Three headers are normally needed for socket/file ioctl's:
 * <sys/ioctl.h>, <sys/filio.h>, and <sys/sockio.h>.
 */
#ifdef	HAVE_SYS_IOCTL_H
# include	<sys/ioctl.h>
#endif
#ifdef	HAVE_SYS_FILIO_H
# include	<sys/filio.h>
#endif
#ifdef	HAVE_SYS_SOCKIO_H
# include	<sys/sockio.h>
#endif

#ifndef	HAVE_PTHREAD_H
# include	<pthread.h>
#endif

#ifdef HAVE_NET_IF_DL_H
# include	<net/if_dl.h>
#endif

#ifdef HAVE_NETINET_SCTP_H
#include	<netinet/sctp.h>
#endif

#ifndef HAVE_ASSERT_H
#include	<assert.h>
#endif

//#define	MAXSIZE		1024	/* max length */

#ifndef TCP_PRE
int tcp_pre(const char* servaddr, const char* port); /*TCP pre*/
#endif

#ifdef CLIENT_CONNECT
int client_connect(int argc, char *servaddr, char *PORT); /*TCP client*/
#endif  

typedef struct
{
    fd_set allset;
    fd_set rset;
    int clients[FD_SETSIZE];        /*数组用于装载各事件描述符*/
    int maxfd;                      /*最大描述符*/ 
    int maxi;
    struct pollfd pclients[1024];
    struct epoll_event events[1024];
    int epollfd;                    /*epoll句柄的返回值*/
    int nready;                     /*创建套接字返回值*/
    int listenfd;
}select_s,poll_p,epoll_e;

#ifndef SELECT_
void select_pre(select_s *s, int listenfd);
void select_do_wait(select_s *s);
void select_handle_accept(select_s *s, struct sockaddr_in *cliaddr, socklen_t *clilen);
void select_add_fd(select_s *s, int fd);
void select_del_fd(select_s *, int);
void select_close(select_s *s);
#endif

#ifndef EPOLL_
void epoll_pre(epoll_e *e, int listenfd);
void epoll_do_wait(epoll_e *e);
void epoll_handle_accept(epoll_e *e, struct sockaddr_in *cliaddr, socklen_t *clilen);
void epoll_add_fd(epoll_e *e, int fd);
void epoll_del_fd(epoll_e *e, int fd);
void epoll_close(epoll_e *e);
#endif

#ifndef POLL_
void poll_pre(poll_p *p, int listenfd);
void poll_do_wait(poll_p *p);
void poll_handle_accept(select_s *s, struct sockaddr_in *cliaddr, socklen_t *clilen);
void poll_add_fd(poll_p *p, int fd);
void poll_del_fd(poll_p *p, int i);
void poll_close(poll_p *p);
#endif 

#ifdef CLIENT_CONNECT
int client_connect(int argc, char *servaddr, char *PORT);
#endif

#ifdef UDP_
int udp_pre(char* PORT);
#endif

#ifdef UDPCLIENT
int udpclient_connect(int argc, char *servaddr);
void udpclient_work(int socketfd, char* servaddr, char* PORT, char* msg);
#endif

#ifndef PROCESS 
ssize_t process_create();
void poll_resource_back(int nchlidren, pid_t *pids);   /* process poll */
#endif

#ifdef PTHREAD_
int pthread_lock_accept(pthread_mutex_t *mutex, int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void pthread_poll_create(Thread *tptr, int nthreads, void*(*thread_main)(void *));
#endif

#ifdef PTHREADS_CREATE
void pthreads_create(pthread_t *tid, const pthread_attr_t *attr, void * (*func)(void *), void *arg)
#endif

long *meter(int nchildren);
void my_filelock_init(char *pathname);
void my_pthreadlock_init(char *pathname, pthread_mutex_t *mptr);
int lock();
int unlock();
void s_signal(int connfd);
int w_wait(int connfd);

int serv_accept(int listenfd, socklen_t clilen, struct sockaddr_in *cliaddr);
void resource_getback(int signo);
void server_work(int connfd);
void Writen(int fd, void *ptr, size_t nbytes);
ssize_t Readline(int fd, void *ptr, size_t maxlen);

#endif /*_ALLNET_H_*/
