#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message , server_reply[2000];
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not creat socket");
	}
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	if(connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	puts("Connected");
	while(recv(socket_desc, server_reply, 2000, 0) > 0)
		{
			puts(server_reply);
			if(server_reply[0] == 'N')
			{
				bzero(server_reply,2000);
				break;
			}
			bzero(server_reply,2000);
		}

	while(1)
	{
		scanf("%s",message);
		if(send(socket_desc, message,strlen(message), 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		if(recv(socket_desc, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
		}
		puts(server_reply);
		bzero(server_reply,2000);
		if(server_reply == "correct")
		{
			return 1;
		}
	}
		

	return 0;
}
