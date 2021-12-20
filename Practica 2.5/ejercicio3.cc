#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>

int main(int argc, char** argv){

    //  argv[1] direccion
    //  argv[2] puerto
    
    struct addrinfo hints;
    struct addrinfo * res;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;

    int error_addr = getaddrinfo(argv[1], argv[2], &hints, &res);

    if (error_addr != 0){
        perror("Se ha producido un error al realizar el getaddrinfo()");
        return 1;
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);   // Creacion del socket UDP

    int dir_local = connect(sock, (struct sockaddr*) res->ai_addr, res->ai_addrlen);      // Conectamos el cliente al servidor

    if(dir_local != 0){
        perror("Se ha producido un error al realizar el bind()");
        return 1;
    }

    char buffer[100];
    scanf("%s", buffer);

    sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    char output[100];
    
    while (buffer != "q"){
        
        sendto(sock, buffer, 80, 0, (struct sockaddr *) &addr, addrlen);
        
        ssize_t c = recvfrom(sock, output, 80, 0, (struct sockaddr *) &addr, &addrlen);
        printf("%s\n", output);
        
        scanf("%s", buffer);

    }

    close(sock);

    return 0;
}
