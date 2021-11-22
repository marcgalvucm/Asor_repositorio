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

#include <sys/time.h>
#include <sys/resource.h>

int main(){

    int politica = sched_getscheduler(0);

    if(politica != -1){
        printf("Politica de planificación: %i\n", politica);

        int priority = getpriority(PRIO_PROCESS, 0);
        int max = sched_get_priority_max(politica);
        int min = sched_get_priority_min(politica);

        if(priority == -1 | max == -1 | min == -1){
            perror("Se ha producido un error");    
        }
        else{
            printf("Prioridad del proceso actual: %i\n", priority);
            printf("Valores máximos y mínimos de la prioridad de la política de planificación: %i,%i\n", max, min);
        }

    }
    else{
        perror("Se ha producido un error con sched_getscheduler()");
    }

}
