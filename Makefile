thread3 client:thread3.c client.c
	gcc -o thread3 thread3.c -lpthread
	gcc -o client client.c
thread3.o client.o:thread3.c client.c
	gcc -c thread3.c
	gcc -c client.c
clean:
	rm*.o thread3 client
