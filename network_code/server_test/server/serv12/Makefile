objects = main.o epoll_handle.o epoll_work.o tcp_pre.o read_write.o 

epoll_server: $(objects)
	gcc -o epoll_server $(objects)

$(objects): allnet.h

main.o: main.c
epoll_handle.o: epoll_handle.c
epoll_work.o: epoll_work.c
tcp_pre.o:tcp_pre.c
read_write.o:read_write.c



.PHONY: clean
clean:
	rm epoll_server $(objects)