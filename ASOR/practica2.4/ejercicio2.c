// STANDARD
#include <stdlib.h>
// I/O
#include <stdio.h>
// PIPES
#include <unistd.h>
// MEMSET
#include <string.h> 
// WAIT
#include <sys/wait.h>

#define N_BYTES 8

int main(int argc, char *argv[]) {
    // Es necesario crear dos tuberías, una para cada sentido
    int p_h[2], h_p[2];

    if (pipe(p_h) == -1 || pipe(h_p) == -1) {
        perror("pipe(..)");
        exit(EXIT_FAILURE);
    }

    printf("== Mensajes de max. %d bytes ==\n", N_BYTES);
    char buf[N_BYTES] = "";
    char end[2] = "";

    pid_t pid = fork();
    switch (pid) {
        // Error
        case -1: {
            perror("fork()");
            exit(EXIT_FAILURE);
        } break;
        // Hijo
        case 0: {
            // Cerrar: escritura padre -> hijo y lectura hijo -> padre
            if (close(p_h[1]) == -1 || close(h_p[0]) == -1) {
                perror("close(..) 1 son");
                exit(EXIT_FAILURE);
            }
            int i = 0;
            while(i < 10) {
                // Resetear el buffer 
                memset(buf, '\0', N_BYTES);
                // Lee de la tuberia p_h
                if (read(p_h[0], &buf, N_BYTES) == -1) {
                    perror("read(..) son");
                    exit(EXIT_FAILURE);
                }
                printf("P -> S ::: RECV: %s\n", buf);

                // Esperara un (1) segundo
                sleep(1);

                if (i < 9) {
                    // Enviara '1' al proceso padre por h_p
                    if (write(h_p[1], "1\0", 2) == -1) {
                        perror("write(..) 1 son");
                        exit(EXIT_FAILURE);
                    }
                    printf("S -> P ::: SEND: 1\n");
                }
                i++;
            }
            // Enviara 'q' al proceso padre por h_p
            if (write(h_p[1], "q\0", 2) == -1) {
                perror("write(..) 1 son");
                exit(EXIT_FAILURE);
            }
            printf("S -> P ::: SEND: q\n");

            // Cerrar: lectura padre -> hijo y escritura hijo -> padre
            if (close(p_h[0]) == -1 || close(h_p[1]) == -1) {
                perror("close(..) 2 son");
                exit(EXIT_FAILURE);
            }
        } break;
        // Padre
        default: {
            // Cerrar: lectura padre -> hijo y escritura hijo -> padre
            if (close(p_h[0]) == -1 || close(h_p[1]) == -1) {
                perror("close(..) 1 par");
                exit(EXIT_FAILURE);
            }

            do {
                // Resetear el buffer 
                memset(buf, '\0', N_BYTES); 
                // Lee de la entrada estandar
                scanf("%s", buf);
                // Limpar el buffer
                strncpy(buf, buf, N_BYTES - 1);
                buf[N_BYTES - 1] = '\0';

                // Escribe en la tuberia p_h
                if (write(p_h[1], buf, N_BYTES - 1) == -1) {
                    perror("write(..) par");
                    exit(EXIT_FAILURE);
                }
                printf("P -> S ::: SEND: %s\n", buf);

                // Lee de la tuberia h_p '1' o 'q'
                if (read(h_p[0], &end, 2) == -1) {
                    perror("read(..) par");
                    exit(EXIT_FAILURE);
                }
                printf("S -> P ::: RECV: %s\n", end);

            } while(strcmp(end, "q\0"));

            // Cerrar: escritura padre -> hijo y lectura hijo -> padre
            if (close(p_h[1]) == -1 || close(h_p[0]) == -1) {
                perror("close(..) 2 par");
                exit(EXIT_FAILURE);
            }

            // Esperar al hijo
            wait(NULL);
        } break;
    }
    return 0;
}