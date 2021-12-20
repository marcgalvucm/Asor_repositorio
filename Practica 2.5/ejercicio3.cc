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

    sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    char buffer[100];

    printf("Comando: %s\n", argv[3]);

    if(sendto(sock, argv[3], 80, 0, (struct sockaddr *) &addr, addrlen) == -1){
        perror("Se ha producido un error al hacer el sendto()");
        return 1;
    }
    
    if(recvfrom(sock, buffer, 100, 0, (struct sockaddr *) &addr, &addrlen) == -1){
        perror("Se ha producido un error al hacer el recvfrom()");
        return 1;
    }

    printf("%s\n", buffer);

    close(sock);

    return 0;
}
