objects = main.o pthread_work.o tcp_pre.o read_write.o server_work.o pthread_serv_accept.o resource_getback.o pthreads_create.o

pthread_server: $(objects)
	gcc -o pthread_server -pthread $(objects)

$(objects): allnet.h

main.o: main.c
pthread_work.o: pthread_work.c
tcp_pre.o: tcp_pre.c
readn_writen.o:read_write.c
server_work.o:server_work.c
pthread_serv_accept.o:pthread_serv_accept.c
resource_getback.o:resource_getback.c
pthreads_create.o:pthreads_create.c

.PHONY: clean
clean:
	rm pthread_server $(objects)
