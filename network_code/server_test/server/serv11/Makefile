objects = main.o poll_handle.o poll_work.o tcp_pre.o read_write.o

poll_server: $(objects)
	gcc -o poll_server $(objects)

$(objects): allnet.h

main.o: main.c
poll_handle.o: poll_handle.c
tcp_pre.o:tcp_pre.c
read_write.o:read_write.c
poll_work.o:poll_work.c

.PHONY: clean
clean:
	rm poll_server $(objects)