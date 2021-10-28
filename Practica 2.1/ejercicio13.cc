#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    timeval start;
    timeval end;

    gettimeofday(&start, NULL);
    for(int i = 0; i < 1000000; i++){}
    gettimeofday(&end, NULL);

    long int resultado = end.tv_usec - start.tv_usec;

    printf("Tiempo que tarda el bucle en microsegundos: %ld\n", resultado);

    return 1;
}
