objects = main.o tcp_pre.o

dyserv: $(objects)
	gcc -o dyserv $(objects)

$(objects): allnet.h

main.o: main.c
tcp_pre.o: tcp_pre.c

.PHONY: clean
clean:
	rm dyserv $(objects)