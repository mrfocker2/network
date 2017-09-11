objects = main.o pthread_mwork.o tcp_pre.o read_write.o server_work.o lock_signal.o

pthreadpoll_server: $(objects)
	gcc -o pthreadpoll_server -pthread $(objects)

$(objects): allnet.h pthread_pollm.h

main.o: main.c
tcp_pre.o: tcp_pre.c
readn_writen.o:read_write.c
server_work.o: server_work.c
pthread_mwork.o: pthread_mwork.c
lock_signal.o: lock_signal.c

.PHONY: clean
clean:
	rm pthreadpoll_server $(objects)
