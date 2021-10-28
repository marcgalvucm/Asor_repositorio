#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    tm* anio;
    time_t* rawtime;

    time(rawtime);
    anio = localtime(rawtime);

    int year = anio->tm_year;
    printf("Año: %i\n", year);

    return 1;
}
