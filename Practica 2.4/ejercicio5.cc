#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

    int fd_tuberia = open("tuberia", O_NONBLOCK | O_RDONLY);    // Abrimos la tuberia "tuberia"
    int fd_tub = open("tub", O_NONBLOCK | O_RDONLY);            // Abrimos la tuberia "tub"

    fd_set rfds;
    FD_ZERO(&rfds); // Inicializamos el conjunto de descriptores para el select
    FD_SET(fd_tuberia, &rfds);  // Añadimos el descriptor de "tuberia" al conjunto
    FD_SET(fd_tub, &rfds);      // Añadimos el descriptor de "tub" al conjunto

    timeval timeout;
    timeout.tv_sec = 5; // Se han elegido 5 segundos por defecto
    timeout.tv_usec = 0;

    char buf_tub[256];      // Buffer donde se va a leer la tuberia 'tub'
    char buf_tuberia[256];  // Buffer donde se va a leer la tuberia 'tuberia'

    int nfds = -1;  

    if(fd_tuberia > fd_tub){
        nfds = fd_tuberia + 1;
    }
    else{
        nfds = fd_tub + 1;
    }

    int cambios = select(nfds, &rfds, NULL, NULL, &timeout);
    
    if(cambios == -1){
        perror("Se ha producido un error al realizar el select()");
    }
    else if(cambios){
        if(read(fd_tub, buf_tub, 256) != 0) printf("Se ha leido desde 'tub' el mensaje: %s", buf_tub);

        if(read(fd_tuberia, buf_tuberia, 256) != 0) printf("Se ha leido desde 'tuberia' el mensaje: %s", buf_tuberia);
    }
    else{
        printf("No ha habido ningun cambio en 5 segundos\n");
    }
    
    return 0;
}
