#include <iostream>
#include <string>
#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main(int arcg, char* argv[]){

    char* comando = argv[1];
    char* argumentos[] = {argv[1], argv[2], NULL};

    pid_t pid = fork();

    if(pid == 0){
        // Proceso hijo
        int result = execvp(comando, argumentos);
        
        if(result == -1){
            perror("Se ha producido un error al ejecutar execvp()");
        }
        else{
            int fd_salida = open("/tmp/daemon.out", O_WRONLY | O_CREAT);
            int salida = dup2(STDOUT_FILENO, fd_salida);

            int fd_error = open("/tmp/daemon.err", O_WRONLY | O_CREAT);
            int error = dup2(STDERR_FILENO, fd_error);

            int fd_entrada = open("/dev/null", O_RDONLY | O_CREAT);
            int entrada = dup2(STDERR_FILENO, fd_entrada);

            if(salida == -1 | error == -1 | entrada == -1){
                perror("Se ha producido un error al hacer el dup2()");
            }
        }

    }
    else if(pid == -1){
        perror("Se ha producido un error al realizar el fork()");
    }
    else{
        // Proceso padre
        while(wait(NULL) == -1);
        
    }
    
    return 0;
}
