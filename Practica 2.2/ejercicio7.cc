#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

	umask(750);

    int puntero = open("/home/usuarioso/Desktop/ficherosPrueba/fichero2.txt", O_CREAT, 645);

    if(puntero == -1){
        perror("Se ha producido un error al crear el fichero");
    }

}
