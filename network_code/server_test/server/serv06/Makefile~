objects = child03m.o lock_fcntl.o serv03m.o read_write.o cputime.o  web_child.o listen.o meter.o
serv03m: $(objects)
	gcc -o serv03m -L.-lnet -lpthread $(objects) 

$(objects): allnet.h

listen.o: listen.c
meter.o: meter.c
child03m.o: child03m.c
cputime.o: cputime.c
lock_fcntl.o: lock_fcntl.c
read_write.o: read_write.c
serv03m.o: serv03m.c
web_child.o: web_child.c

.PHONY: clean
clean:
	rm serv03m $(objects)
