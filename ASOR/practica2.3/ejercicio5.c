/**     == Ejercicio 5. ==
    Escribir un programa que muestre los identificadores del
    proceso (PID, PPID, PGID y SID), el número máximo de 
    ficheros que puede abrir y su directorio de trabajo actual.
*/

// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>
// ID PROCESOS
#include <unistd.h>
// LIMITE DE RECURSOS
#include <sys/time.h>
#include <sys/resource.h>

int main (int argc, char *argv[]) {
    // (PID, PPID, PGID y SID). ver diap 2.3 - 9, 10, 11
    printf("PID:    %d  - ID unico\n", getpid());
    printf("PPID:   %d  - ID proceso que lo creo\n", getppid());
    printf("PGID:   %d  - ID grupo de procesos\n", getpgid(getpid()));
    printf("SID:    %d  - ID de la sesion\n", getsid(getppid()));

    // El número máximo de ficheros que puede abrir. ver diap 2.3 - 20
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        exit(EXIT_FAILURE);
    }
    printf("RLIM:   %d  - Numero max de ficheros\n", limit.rlim_max);

    // Su directorio de trabajo actual. ver diap 2.3 - 12
    printf("DIR:    %s\n", getcwd(NULL, limit.rlim_max));

    return 0;
}