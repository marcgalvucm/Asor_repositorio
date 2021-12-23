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

    struct addrinfo hints;
    struct addrinfo * res;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int error_addr = getaddrinfo(argv[1], argv[2], &hints, &res);

    if (error_addr == -1){
        perror("Se ha producido un error al realizar el getaddrinfo()");
        return 1;
    }

    int sock = socket(res->ai_family, res->ai_socktype, 0);

    sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    int conexion = connect(sock, (struct sockaddr *) &addr, addrlen);

    if(conexion == -1){
        perror("Se ha producido un error al realizar el connect()");
        close(conexion);
        return 1;
    }

    int c;
    char buffer[80];

    send(conexion, buffer, c, 0);

    while (buffer != "Q"){
        c = recv(conexion, buffer, 80, 0);
        send(conexion, buffer, c, 0);
    }
    
    close(conexion);

    return 0;
}
