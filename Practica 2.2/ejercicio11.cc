#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

	int enlaceLink = link("/home/usuarioso/Desktop/ficherosPrueba/fichero.txt", "/home/usuarioso/Desktop/ficherosPrueba/fichero.hard");
    if(enlaceLink == -1){
        perror("Ha habido un problema al realizar el link()");
    }
    else{
        int enlaceSymlink = symlink("/home/usuarioso/Desktop/ficherosPrueba/fichero.txt", "/home/usuarioso/Desktop/ficherosPrueba/fichero.sym");
        if(enlaceSymlink == -1){
            perror("Ha habido un problema al realizar el symlink()");
        }
    }

}
