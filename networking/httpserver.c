#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080
int main(){
    // Step 1: create a socket
    int socket_fd;
    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Error creating socket "); 
        return 0; 
    }
    // Step 2: Identify/name a socket assign it a port via bind()
    struct sockaddr_in address;
    /* htonl converts a long integer (e.g. address) to a network representation */ 
    /* htons converts a short integer (e.g. port) to a network representation */ 
    memset((void *)&address, 0, sizeof(address)); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 
    int addrlen = sizeof(address);
    if(bind(socket_fd,(struct sockaddr *)&address,sizeof(address)) < 0) 
    { 
        perror("Error binding "); 
        return 1; 
    }
    // Step 3: wait for incoming connections with listen() and accept() them
    if (listen(socket_fd, 10) < 0){
        perror("Error listening ");
        return 1;
    }
    int current_sock;
    char *msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    while(1){
        puts("---------------Waiting-------------------");
        if((current_sock = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){
            perror("Error accepting ");
            return 1;
        }
        // Step 4: Receive and send
        char buffer[30000] = {0};
        read(current_sock, buffer, 30000);
        printf("Received: %s\n", buffer);
        write(current_sock, msg, strlen(msg));
        puts("--------------Message Sent-------------");
        // Step 5: close the socket
        close(current_sock);
    }
    puts("Looks good to me!");
    return 0;
}