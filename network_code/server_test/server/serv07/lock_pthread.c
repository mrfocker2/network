/* include my_lock_init */
#include 	"allnet.h"
#include	<sys/mman.h>

//static pthread_mutex_t	*mptr;	/* actual mutex will be in shared memory */

void
my_pthreadlock_init(char *pathname, pthread_mutex_t	*mptr)
{
	int		fd;
	pthread_mutexattr_t	mattr;

	fd = open("/dev/zero", O_RDWR, 0);

	mptr = mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE,
				MAP_SHARED, fd, 0);
	close(fd);

	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(mptr, &mattr);
}
