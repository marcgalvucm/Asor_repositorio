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

    int dir_local = bind(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen);      // Asociar la dirección local a un socket

    if(dir_local != 0){
        perror("Se ha producido un error al realizar el bind()");
        return 1;
    }

    for(int i = 0; i < 2; i++){
        pid_t pid = fork();

        if(pid == -1){
            perror("Se ha producido un error al realizar el fork()");
        }
        else if(pid == 0){
            // Proceso hijo
            printf("Proceso hijo");

            char buffer[100];

            sockaddr_storage addr;
            socklen_t addrlen = sizeof(addr);

            ssize_t c = recvfrom(sock, buffer, 80, 0, (struct sockaddr *) &addr, &addrlen);

            char host[NI_MAXHOST];
            char server[NI_MAXSERV];

            getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

            if(buffer[0] == 't'){
                printf("Recibidos %d bytes de %s: %s\n", c, host, server);

                time_t rawtime;
                struct tm* info;
                time(&rawtime);
                info = localtime(&rawtime);
                char output[128];
                strftime(output,128,"%H%M:%S",info);

                sendto(sock, output, c, 0, (struct sockaddr *) &addr, addrlen);

            }
            else if(buffer[0] == 'd'){
                printf("Recibidos %d bytes de %s: %s\n", c, host, server);

                time_t rawtime;
                struct tm* info;
                time(&rawtime);
                info = localtime(&rawtime);
                char output[200];
                strftime(output,200,"%y-%m-%d",info);

                sendto(sock, output, c, 0, (struct sockaddr *) &addr, addrlen);
            }
            else if(buffer[0] == 'q'){
                printf("Saliendo...\n");
            }
            else{
                printf("Comando %s no soportado\n", buffer);
            }

            printf("PID: %i\n", pid);
            kill(getpid(), SIGTERM);
        }
        else{
            // Proceso padre
        }
    }

    close(sock);

    return 0;
}
