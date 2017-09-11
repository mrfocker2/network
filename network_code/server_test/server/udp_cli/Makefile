objects = main.o udpclient_connect.o udpclient_work.o

udpclient: $(objects)
	gcc -o udpclient $(objects)

$(objects): allnet.h

main.o: main.c
udpclient_connect.o: udpclient_connect.c
udpclient_work.o:udpclient_work.c

.PHONY: clean
clean:
	rm udpclient $(objects)