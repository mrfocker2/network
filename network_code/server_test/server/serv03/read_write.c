#include "allnet.h"

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char c, *ptr;
	ptr = (char*)vptr;
	for (n = 1; n < maxlen; n++) 
	{
		if ((rc = read(fd, &c, 1)) == 1) 
		{
			*ptr++ = c;
			if (c == '\n')
				break;
		} 
		else if (rc == 0) 
		{
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} 
		else
			return(-1);	/* error */
	}
	*ptr = 0;
	return(n);
}

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
	ssize_t	n;
	if ((n = readline(fd, ptr, maxlen)) == -1)
		printf("readline error\n");
	return(n);
}

ssize_t	writen(int fd, const void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nwritten;
	const char *ptr;
	ptr = (char*)vptr;
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