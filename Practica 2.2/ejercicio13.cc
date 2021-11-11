#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argv){

    int descriptorFichero = argv;

    int copyFd = dup(descriptorFichero);

    if(copyFd == -1){
        write(copyFd, "Se ha producido un error al hacer dup()", 60);
        perror("Se ha producido un error al hacer dup()");
    }
    else{
        write(copyFd, "Cadena de prueba \n", 20);
    }

}
