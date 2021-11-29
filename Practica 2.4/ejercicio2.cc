#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#include <sys/types.h>
#include <fcntl.h>

#define SIZE 512

int main(int argc, char* argv[]){

    // Creamos las tuberías sin nombre
    int a[2];
    int b[2];
    int p_h = pipe(a);  // Tubería p_h (padre a hijo)
    int h_p = pipe(b);  // Tuberia h_p (hijo a padre)

    // Creamos el hijo
    pid_t pid;
    pid = fork();

    if(pid == -1){
        perror("Se ha producido un error al realizar el fork()");
    }
    else if(pid == 0){
        // Proceso hijo
        
        close(a[1]);   // Cerramos el extremo de escritura de la tubería
        close(b[0]);   // Cerramos el extremo de lectura de la tubería

        int mensajes = 0;
        char buff_hijo[SIZE];

        while (mensajes < 10){
            if(read(a[0], buff_hijo, SIZE) == -1){
                perror("Se ha producido un error al realizar el read()");
            }
            else{
                mensajes++;
                printf("Mensaje: %s\n", buff_hijo); // Imprimimos el mensaje por la salida estandar
                sleep(1);   // Espera un segundo
                if(mensajes == 10){
                    write(b[1], "q", SIZE); // Indica al padre que finalice
                }
                else{
                    write(b[1], "l", SIZE); // Indica al padre que está listo para seguir
                }
            }   
        }
        
        close(a[0]);
        close(b[1]);   // Cerramos el extremo de escritura de la tubería
        
    }
    else{
        // Proceso padre

        close(a[0]);
        close(b[1]);

        char buff_padre[SIZE];
        char cadena[SIZE];
        
        printf("Introduzca cadena: ");
        scanf("%s", cadena);

        write(a[1], cadena, SIZE);
        read(b[0], buff_padre, SIZE);
        while (strcmp(buff_padre, "l") == 0){
            printf("Introduzca cadena: ");
            scanf("%s", cadena);

            write(a[1], cadena, SIZE);
            read(b[0], buff_padre, SIZE);   // Se queda bloqueado hasta que hay algun mensaje en la tuberia
        }
        
        close(a[1]);   // Cerramos el extremo de escritura de la tubería
        close(b[0]);

    }

    return 0;

}
