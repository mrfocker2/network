objects = main.o tcp_pre.o read_write.o select_handle.o select_work.o

select_server: $(objects)
	gcc -o select_server $(objects)

$(objects): allnet.h

main.o: main.c
select_handle.o: select_handle.c
tcp_pre.o:tcp_pre.c
read_write.o:read_write.c
select_work.o:select_work.c


.PHONY: clean
clean:
	rm select_server $(objects)