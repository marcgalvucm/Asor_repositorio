#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

    for(int i = 0; i < 255; i++){
        printf("%i : ", i);
        printf(strerror(i));
        printf("\n");
    }

    return 1;
}
