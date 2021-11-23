#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main(int arcg, char* argv[]){

    sigset_t blk_set;

    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGUSR1);

    sigprocmask(SIG_BLOCK, &blk_set, NULL);
    
    /* Código protegido */
    
    sigset_t pendientes;
    
    sigpending(&pendientes);
    
    int segundos = atoi(argv[1]);
    sleep(segundos);

    if(!sigismember(&pendientes, SIGUSR1)){
        if(unlink("ejercicio13") != 0){
            perror("Se ha producido un error al hacer unlink()");
        }
    }
    else{
        sigsuspend(&blk_set);
    }

    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

    return 0;
}
