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

int main(){

    pid_t pid = fork();

    if(pid == 0){
        // Proceso hijo

        if(chdir("/tmp") == -1){
            perror("Se ha producido un error al realizar el chdir()");
        }
        else{
            pid_t pid = getpid();
            pid_t pid_padre = getppid();
            pid_t pid_grupo = getpgid(pid);
            pid_t pid_sesion = getsid(pid);

            printf("Pid del proceso: %d\n", pid);
            printf("Pid del proceso padre: %d\n", pid_padre);
            printf("Identificador del grupo: %d\n", pid_grupo);
            printf("Identificador de la sesion: %d\n", pid_sesion);
        }
    }
    else if(pid == -1){
        perror("Se ha producido un error al realizar el fork()");
    }
    else{
        // Proceso padre
        sleep(1);
    }

}
