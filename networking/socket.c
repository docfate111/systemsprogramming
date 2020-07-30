#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
int get(const char* ip_addr, int port_num, const char* data){
	int socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if ( socket_desc == -1){
		printf("Could not create socket");
	}
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(ip_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons( port_num );
	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0){
		puts("connect error");
		return 1;
	}
	puts("Connected");
	char* message = (char*)malloc(60);
	snprintf(message, 60, "GET /%s HTTP/1.1", data);
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	return 0;
}

int main(int argc, char** argv){
	get("127.0.0.1", 8000, "file.html");
	return 0;
}
