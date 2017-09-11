objects = main.o processpoll_work.o tcp_pre.o read_write.o server_work.o kill_process.o

processpoll_server: $(objects)
	gcc -o processpoll_server $(objects)

$(objects): allnet.h

main.o: main.c
process_work.o: processpoll_work.c
tcp_pre.o: tcp_pre.c
readn_writen.o:read_write.c
server_work.o: server_work.c
kill_process.o:kill_process.c

.PHONY: clean
clean:
	rm processpoll_server $(objects)