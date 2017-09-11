objects = main.o process_work.o tcp_pre.o server_work.o process_serv_accept.o read_write.o process_create.o resource_getback.o

process_server: $(objects)
	gcc -o process_server $(objects)

$(objects): allnet.h

main.o: main.c
process_work.o: process_work.c
tcp_pre.o:tcp_pre.c
server_work.o:server_work.c
process_serv_accept.o:process_serv_accept.c
read_write.o:read_write.c
process_create.o:process_create.c
resource_getback.o:resource_getback.c

.PHONY: clean
clean:
	rm process_server $(objects)