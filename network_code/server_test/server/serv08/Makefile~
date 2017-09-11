objects = main.o pthreadpoll_work.o tcp_pre.o read_write.o pthreadpoll_lock.o server_work.o pthread_poll_create.o

pthreadpoll_server: $(objects)
	gcc -o pthreadpoll_server -pthread $(objects)

$(objects): allnet.h pthread_polle.h

main.o: main.c
pthread_work.o: pthreadpoll_work.c
tcp_pre.o: tcp_pre.c
readn_writen.o:read_write.c
pthreadpoll_lock.o: pthreadpoll_lock.c
server_work.o: server_work.c
pthread_poll_create.o:pthread_poll_create.c

.PHONY: clean
clean:
	rm pthreadpoll_server $(objects)
