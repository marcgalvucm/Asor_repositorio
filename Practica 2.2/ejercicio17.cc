#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

int main(int arcg, char* argv[]){

    char* directorio = argv[1];
    int length = 0;

    DIR* fdir = opendir(directorio);
    if(fdir != NULL){
        struct dirent* d = readdir(fdir); 

        while(d != NULL){

            struct stat st;

            char path[100];
            strcat(strcpy(path, directorio), d->d_name); 

            //printf("Path: %s\n", path);

            if(stat(path, &st) == 0){
                if(st.st_mode & S_IFDIR) printf("%s/ \n", d->d_name);
                else if(st.st_mode & S_IFREG){
                    printf("%s \n", d->d_name);
                    length += st.st_size;
                } 
                else if(st.st_mode & S_IEXEC){
                    printf("%s* \n", d->d_name);
                    length += st.st_size;
                } 
            }
            else{
                perror("Se ha producido un error con stat()");
            }

            d = readdir(fdir);

        }

        printf("Tamaño total: %i\n", length);
    }
    else{
        perror("Se ha producido un error con el opendir()");
    }

}
