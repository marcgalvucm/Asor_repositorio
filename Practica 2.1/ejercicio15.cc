#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    char buffer[200];
    tm* anio;
    time_t rawtime;

    time(&rawtime);
    anio = localtime(&rawtime);

    strftime(buffer, 200, "Hoy es %A, %d de %B de %Y, %r", anio);
    printf("%s\n", buffer);

    return 1;
}
