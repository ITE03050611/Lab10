thread1:thread1.c
	gcc -o thread1 thread1.c -lpthread
thread1.o:thread1.c
	gcc -c thread1.c
clean:
	rm*.o thread1
