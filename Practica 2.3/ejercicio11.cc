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
#include <stdlib.h>

#include <signal.h>

int main(int arcg, char* argv[]){

    sigset_t blk_set;

    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);
    sigaddset(&blk_set, SIGTSTP);

    sigprocmask(SIG_BLOCK, &blk_set, NULL);
    
    /* Código protegido */
    
    char *sleep_secs = getenv("SLEEP_SECS");

    int segundos = atoi(sleep_secs);

    sleep(segundos);

    sigset_t pendientes;
    sigpending(&pendientes);

    if(sigismember(&pendientes, SIGINT)){
        printf("Se ha recibido la señal SIGINT \n");
    }
    
    if(sigismember(&pendientes, SIGTSTP)){
        printf("Se ha recibido la señak SIGSTP \n");
    }

    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

    return 0;
}
