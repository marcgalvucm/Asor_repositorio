#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

	struct stat* statbuf;

	int resultado = stat("/home/usuarioso/Desktop/ficherosPrueba/fichero2.txt",statbuf);
	if(resultado == -1){
		perror("Se ha producido un error en la funcion stat()");
	}
	else{
		printf("Inodo del fichero: %li\n", statbuf->st_ino);
		printf("Tipo de fichero: %d\n", statbuf->st_mode);
		printf("Hora que se accedio por ultima vez: %i\n", statbuf->st_atim);
	}
	
}
