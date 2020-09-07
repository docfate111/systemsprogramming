#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
int main(){
    // Step 1: create a socket
    int socket_fd;
    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Error creating socket!"); 
        return 0; 
    }
    // Step 2: Identify/name a socket assign it a port via bind()
    struct sockaddr_in address;
    const int PORT = 8080; //Where the clients can reach at
    /* htonl converts a long integer (e.g. address) to a network representation */ 
    /* htons converts a short integer (e.g. port) to a network representation */ 
    memset((char *)&address, 0, sizeof(address)); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons(PORT); 
    if (bind(socket_fd,(struct sockaddr *)&address,sizeof(address)) < 0) 
    { 
        perror("Error binding!"); 
        return 0; 
    }
    puts("Looks good to me!");
    return 0;
}