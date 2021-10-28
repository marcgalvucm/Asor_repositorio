#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main(){
    
    passwd* pass;

    pass = getpwuid(getuid());

    printf("UID real del usuario: %d\n", getuid());
    printf("UID efectivo del usuario: %d\n", geteuid());
    printf("Nombre del usuario: %s\n", pass->pw_name);
    printf("Directorio home: %s\n", pass->pw_dir);
    printf("Descripcion del usuario: %s\n", pass->pw_gecos);

    return 1;
}
