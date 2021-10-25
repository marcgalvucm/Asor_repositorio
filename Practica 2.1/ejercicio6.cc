#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <limits.h>

int main(){
    
    printf("Longitud maxima de los argumentos: %i \n", sysconf(_SC_ARG_MAX));
    printf("Numero maximo de hijos : %i \n", sysconf(_SC_CHILD_MAX));
    printf("Numero maximo de ficheros : %i \n", sysconf(_SC_OPEN_MAX));

    return 1;
}
