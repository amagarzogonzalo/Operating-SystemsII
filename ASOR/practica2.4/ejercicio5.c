/**
    TERMINAL 1
[cursoredes@localhost practica2.4]$ gcc ejercicio5.c 
[cursoredes@localhost practica2.4]$ ./a.out 
    TERMINAL 2
[cursoredes@localhost practica2.4]$ echo "kpasa" > pipe1
*/

// STANDARD
#include <stdlib.h>
// I/O
#include <stdio.h>
// WRONLY
#include <fcntl.h>
// STRING
#include <string.h>
// SELECT
#include <sys/select.h>

#define N_BYTES 8

int main(int argc, char **argv){
    // Ejercicio sin argumentos
    if (argc > 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("El programa leera %d bytes\n", N_BYTES);

    char pipe_one[] = "./pipe1";
    char pipe_two[] = "./pipe2";

    printf("Channel one: %s\nChannel two: %s\n",
        pipe_one,
        pipe_two
    );

    mkfifo(pipe_one, 0777);
    mkfifo(pipe_two, 0777); 

    // Abrir los descriptores
    int fd1, fd2;
    // La apertura de la tubería para lectura se bloqueara. Usa O_NONBLOCK en open(2)
    if ((fd1 = open(pipe_one, O_RDONLY | O_NONBLOCK)) == -1 ||
        (fd2 = open(pipe_two, O_RDONLY | O_NONBLOCK)) == -1) {
        perror("open(..)");
        exit(EXIT_FAILURE);
    }
    
    // Para optimizar las operaciones de lectura usar un buffer
    char buffer[N_BYTES];

    int maxfd = (fd1 > fd2) ? fd1 + 1 : fd2 + 1;

    // Plantilla Mult. E/S Sincrona. ver diap. 2.3 - 49
    fd_set rfds;

    FD_ZERO(&rfds);
    FD_SET(fd1, &rfds);
    FD_SET(fd2, &rfds);

    struct timeval timeout;
    timeout.tv_sec = 8;
    timeout.tv_usec = 0;

    int cambios = select(maxfd, &rfds, NULL, NULL, &timeout);
    if (cambios == -1) {
        perror("select(..)");
    }
    else if (cambios) {
        // Resetear el buffer
        memset(buffer, '\0', N_BYTES);
        if (FD_ISSET(fd1, &rfds)) {
            read(fd1, buffer, N_BYTES - 1);
            // Procesar el buffer
            buffer[N_BYTES - 1] = '\0';
            // El programa debe mostrar la tuberia y los datos
            printf("%s :: RECV: %s", pipe_one, buffer);
        }
        else if (FD_ISSET(fd2, &rfds)) {
            read(fd2, buffer, N_BYTES - 1);
            // Procesar el buffer
            buffer[N_BYTES - 1] = '\0';
            // El programa debe mostrar la tuberia y los datos
            printf("%s :: RECV: %s", pipe_two, buffer);
        }
    } else {
        printf("Ningun dato nuevo en 8 segs.\n");
    }

    // Cerrar los descriptores
    close(fd1);
    close(fd2);

    return 0;
}