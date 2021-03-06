#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
typedef struct{
	char *address;
	int port_num;
} lump;
void* get(void* arg){
	lump* argh = arg;
	char* ip_addr = argh->address;
	int port_num = argh->port_num;
	const char* data =  "";
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
		return NULL;
	}
	puts("Connected");
	char* message = (char*)malloc(60);
	snprintf(message, 60, "GET /%s HTTP/1.1\r\n\r\n", data);
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Request failed");
		return NULL;
	}
	puts(message);
	puts("Request Sent\n");
	char server_reply[2000];
	if( recv(socket_desc, server_reply, 2000, 0) < 0 ){
		puts("Response failed");
	}
	puts("Response received!");
	puts(server_reply);
	close(socket_desc);
	return NULL;
}

char* convert_hostname(char* hostname){
	char* ip = (char*)malloc(20);
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	if ( (he = gethostbyname( hostname ) ) == NULL){
		//gethostbyname failed
		herror("gethostbyname");
		return NULL;
	}
	//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	addr_list = (struct in_addr **) he->h_addr_list;
	for(i = 0; addr_list[i] != NULL; i++){
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
	}
	return ip;
}
int isIp(char* b){
	int count = 0;
	for(size_t i=0; i<strlen(b); i++){
		if(*(b+i)=='.'){
			count++;
		}
	}
	return count==3;
}
int main(int argc, char* argv[]){
	if(argc<3){
		printf("Usage <%s>: <url/ip address> <port>", argv[0]);
		return 0;
	}
	lump* l = (lump*)malloc(sizeof(lump));
	char *url = (char*)malloc(12);
	strncpy(url, argv[1], 12);
	char* p = (char*)malloc(4);
	strncpy(p, argv[2], 4);
	l->address = (char*)malloc(20);
	if(!isIp(url)){
		l->address = convert_hostname(url);
	}else{
		l->address = url;
	}
	l->port_num = atoi(p);
	pthread_t th;
	int status = pthread_create(&th, NULL, get, (void*)l);
	pthread_join(th, NULL);
	return 0;
}
