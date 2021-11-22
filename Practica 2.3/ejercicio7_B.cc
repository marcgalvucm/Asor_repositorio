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

    int resultado = system(comando);

    printf("El comando terminó de ejecutarse \n");

    return 0;
}
