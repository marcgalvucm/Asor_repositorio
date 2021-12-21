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

    if (error_addr != 0){
        perror("Se ha producido un error al realizar el getaddrinfo()");
        return 1;
    }

    int sock = socket(res->ai_family, res->ai_socktype, 0);
    int dir_local = bind(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen);      // Asociar la dirección local a un socket

    if(dir_local != 0){
        perror("Se ha producido un error al realizar el bind()");
        return 1;
    }

    int escuchas = listen(sock, 5);
    if(escuchas != 0){
        perror("Se ha producido un error al realizar el listen()");
        return 1;
    }

    sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    char host[NI_MAXHOST];
    char server[NI_MAXSERV];

    int clisd = accept(sock, (struct sockaddr *) &addr, &addrlen);

    getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

    printf("Conexion desde %s:%s\n", host, server);

    int c;
    char buffer[80];

    while (c = recv(clisd, buffer, 80, 0)){
        send(clisd, buffer, c, 0);
    }
    
    close(clisd);

    return 0;
}
