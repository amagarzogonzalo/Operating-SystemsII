// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>
// FORKS
#include <unistd.h>
#include <sys/types.h>  // pid_t

int main(int argc, char *argv[]) {
    // Plantilla fork. ver diap 2.3 - 15
    pid_t pid;
    pid = fork();

    switch (pid) {
        case -1: {
            perror("fork");
            exit(EXIT_FAILURE); 
        }
        case 0: {
            printf("    Hijo %i (padre: %i)\n", getpid(), getppid());
            if (chdir("/tmp") == -1) {
                perror("chdir");
                exit(EXIT_FAILURE);
            }
            sleep(3);
            exit(EXIT_SUCCESS);
        } break;

        default: {
            printf("Padre %i (hijo: %i)\n", getpid(), pid);
            // (PID, PPID, PGID y SID). ver diap 2.3 - 9, 10, 11
            printf("PID:    %d  - ID unico\n", getpid());
            printf("PPID:   %d  - ID proceso que lo creo\n", getppid());
            printf("PGID:   %d  - ID grupo de procesos\n", getpgid(getpid()));
            printf("SID:    %d  - ID de la sesion\n", getsid(getppid()));
            exit(EXIT_SUCCESS);
        } break;
    }
    return 0;
}

/*
[cursoredes@localhost practica2.2]$ ./a.out 
Padre 12453 (hijo: 12454)
PID:    12453  - ID unico
PPID:   4043  - ID proceso que lo creo
PGID:   12453  - ID grupo de procesos
SID:    4043  - ID de la sesion
    Hijo 12454 (padre: 1)
[cursoredes@localhost practica2.2]$ ps
  PID TTY          TIME CMD
 4043 pts/0    00:00:00 bash
12454 pts/0    00:00:00 a.out
12461 pts/0    00:00:00 ps
*/