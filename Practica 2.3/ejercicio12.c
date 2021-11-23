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

volatile int contadorSIGINT = 0;
volatile int contadorSIGTSTP = 0;

void manejador(int a){

    switch (a)
    {
    case SIGINT:
        contadorSIGINT++;
        break;
    case SIGTSTP:
        contadorSIGTSTP++;
        break;
    default:
        break;
    }

}


int main(int arcg, char* argv[]){

    sigset_t blk_set;

    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);
    sigaddset(&blk_set, SIGTSTP);

    sigprocmask(SIG_BLOCK, &blk_set, NULL);
    
    /* Código protegido */
    
    
    sigset_t pendientes;

    struct sigaction sig;

    sig.sa_handler = &manejador;

    while(contadorSIGINT < 10 | contadorSIGTSTP < 10){
        
        sigpending(&pendientes);

        if(sigismember(&pendientes, SIGINT)){
            
            if(sigaction(SIGINT, &sig, NULL) != 0){
                perror("Se ha producido un error con el sigaction()");
            }
            else{
                sigemptyset(&sig.sa_mask);
        }
        
        if(sigismember(&pendientes, SIGTSTP)){

            if(sigaction(SIGTSTP, &sig, NULL) != 0){
                perror("Se ha producido un error con el sigaction()");
            }
            else{
                sigemptyset(&sig.sa_mask);
            }
        }

    }

    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

    return 0;
}

