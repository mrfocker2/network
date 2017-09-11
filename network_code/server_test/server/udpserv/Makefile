objects = main.o udp_pre.o udp_work.o

udpserver: $(objects)
	gcc -o udpserver $(objects)

$(objects): allnet.h

main.o: main.c
udp_pre.o: udp_pre.c
udp_work.o:udp_work.c

.PHONY: clean
clean:
	rm udpserver $(objects)