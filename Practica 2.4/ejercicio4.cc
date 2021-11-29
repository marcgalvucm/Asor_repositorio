#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

    int fd = open("tuberia", O_WRONLY);

    if(fd != -1){   // No se ha producido ningún error
        write(fd, argv[1], 512);  // Escribimos en la tubería
    }
    else{
        perror("Se ha producido un error al abrir la tuberia con nombre");
    }

    return 0;
}
