#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(){

    int fd = open("fich.txt", O_RDWR);

    if(lockf(fd, F_TLOCK, 1) != -1){
        time_t t = time(NULL);
        struct tm tiempo = *localtime(&t);
        
        printf("Hora actual: %i:%i:%i \n", tiempo.tm_hour, tiempo.tm_min, tiempo.tm_sec);

        sleep(30);
        lockf(fd, F_ULOCK, 1);
    }
    else{
        perror("Ha habido un error con lockf()");
    }

}
