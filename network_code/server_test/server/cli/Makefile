objects = main.o client_connect.o

client: $(objects)
	gcc -o client $(objects)

$(objects): allnet.h

main.o: main.c
client_connect.o: client_connect.c
.PHONY: clean
clean:
	rm client $(objects)