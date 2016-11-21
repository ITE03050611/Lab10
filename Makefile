thread2:thread2.c
	gcc -o thread2 thread2.c -lpthread
thread2.o:thread2.c
	gcc -c thread2.c
clean:
	rm*.o thread2
