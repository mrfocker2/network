objects = child04.o lock_pthread.o serv07.o read_write.o cputime.o  web_child.o meter.o
serv07: $(objects)
	gcc -o serv07 -L. -lnet -lpthread $(objects) 

$(objects): allnet.h pthread_pollm.h

meter.o: meter.c
child04.o: child04.c
cputime.o: cputime.c
lock_pthread.o: lock_pthread.c
read_write.o: read_write.c
serv07.o: serv07.c
web_child.o: web_child.c

.PHONY: clean
clean:
	rm serv04 $(objects)