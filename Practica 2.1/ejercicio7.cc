#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <limits.h>

int main(){
    
    printf("Numero maximo de enlaces: %ld \n", pathconf("/",_PC_LINK_MAX));
    printf("Tamaño maximo de una ruta : %ld \n", pathconf("/",_PC_PATH_MAX));
    printf("Nombre de fichero : %ld \n", pathconf("/", _PC_NAME_MAX));

    return 1;
}
