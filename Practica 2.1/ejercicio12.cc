#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    time_t* t;
    printf("Tiempo en segundos desde el Epoch: %ld\n" , time(t));

    return 1;
}
