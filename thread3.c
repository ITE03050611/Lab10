#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>   
#include<pthread.h>
void *connection_handler(void *);
int main(int argc , char *argv[])
{
int socket_desc , new_socket , c , *new_sock;
struct sockaddr_in server , client;
char *message;

socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}

server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8888 );

if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("bind failed");
return 1;
}
puts("bind done");

listen(socket_desc , 3);

puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
{
puts("Connection accepted");

message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
write(new_socket , message , strlen(message));
pthread_t sniffer_thread;
new_sock = malloc(1);
*new_sock = new_socket;
if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
{
perror("could not create thread");
return 1;
}

puts("Handler assigned");
}
if (new_socket<0)
{
perror("accept failed");
return 1;
}
return 0;
}

void *connection_handler(void *socket_desc)
{
int new_socket = *(int*)socket_desc;
int read_size;
char *message,client_Num[4],reAB[10];


		int i, j, tmp=0, a, b, c, d,randNum, A, B;
		int e[5040][4];
		char ans[4];
		srand(time(0));
		for (i=0;i<10000;i++)
		{
			a = (i/1)%10;
			b = (i/10)%10;
			c = (i/100)%10;
			d = (i/1000)%10;
			if (a!=b && a!=c && a!=d && b!=c && b!=d && c!=d)
			{
				e[tmp][0] = d;
				e[tmp][1] = c;
				e[tmp][2] = b;
				e[tmp][3] = a;
				tmp++;
			}
		}
		randNum = (rand()%5040);
		printf("%d%d%d%d\n",e[randNum][0],e[randNum][1],e[randNum][2],e[randNum][3]);
		sprintf(ans,"%d",e[randNum][0]*1000+e[randNum][1]*100+e[randNum][2]*10+e[randNum][3]);
		while(1)
		{
			A=0, B=0;
			bzero(client_Num,4);
			read(new_socket,client_Num,4);
			for (i=0;i<4;i++)
			if (client_Num[i] == ans [i])
					A++;
			for (i=0;i<4;i++)
				for (j=0;j<4;j++)
					if (client_Num[i] == ans[j] && i!=j)
						B++;
			if (A==4)
			{
				message = "correct";
				write(new_socket, message, strlen(message)+1);
				break;			
			}
			else
			{
				sprintf(reAB,"%dA%dB",A,B);
				write(new_socket, reAB, strlen(reAB)+1);
			}
		}
		return 0;
}
