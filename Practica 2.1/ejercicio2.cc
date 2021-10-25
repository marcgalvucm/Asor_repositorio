#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

    if(setuid(2) == -1){
        // gestion del error
        perror("Se ha producido un error con setuid()");
        printf(strerror(errno));
        printf("/n Version numerica: %i\n", errno);
    }

    return 1;
}
