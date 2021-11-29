#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

#define SIZE 512

int main(int argc, char* argv[]){

    // Creamos la tubería sin nombre
    int fd[2];
    pipe(fd);

    // Creamos el hijo
    pid_t pid;
    pid = fork();

    if(pid == -1){
        perror("Se ha producido un error al realizar el fork()");
    }
    else if(pid == 0){
        // Proceso hijo
        
        close(fd[1]);   // Cerramos el extremo de escritura de la tubería
        dup2(fd[0], 0); // Redirigimos la entrada estandar al extremo de lectura de la tubería
        close(fd[0]);   // Cerramos el extremo de lectura de la tubería

        execlp(argv[3], argv[3], argv[4], NULL);    // Ejecutamos el comando        

    }
    else{
        // Proceso padre
        
        close(fd[0]);   // Cerramos el extremo de lectura de la tubería
        dup2(fd[1], 1); // Redirigimos la salida estandar al extremo de escritura de la tubería
        close(fd[1]);   // Cerramos el extremo de escritura de la tubería

        execlp(argv[1], argv[1], argv[2], NULL);    // Ejecutamos el comando
    }

    return 0;

}
