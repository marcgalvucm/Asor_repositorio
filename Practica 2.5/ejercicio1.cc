#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <iostream>

int main(int argc, char** argv){

    struct addrinfo hints;
    struct addrinfo * res;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    //hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    int error_addr = getaddrinfo(argv[1], NULL, &hints, &res);

    if (error_addr != 0){
        perror("Se ha producido un error al realizar el getaddrinfo()");
        return 1;
    }

    struct addrinfo* i;

    for(i = res; i != NULL; i = i->ai_next){
        char host[NI_MAXHOST];
        char server[NI_MAXSERV];

        int error_name = getnameinfo(i->ai_addr, i->ai_addrlen, host, NI_MAXHOST, server, NI_MAXSERV, AI_NUMERICHOST);
        if(error_name != 0) perror("Se ha producido un error al realizar el getnameinfo()");
        else{
            printf("%s, %i, %i \n", host, i->ai_family, i->ai_socktype);
        }

    }

    return 0;
}
