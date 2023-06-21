// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>
// FORKS & FILES
#include <unistd.h>
#include <sys/types.h>  // pid_t
#include <fcntl.h>      // O_CREAT | O_RDWR
// ERROR EXIT
#include <errno.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Plantilla fork. ver diap 2.3 - 15
    pid_t pid;
    pid = fork();

    switch (pid) {
        case -1: {
            perror("fork");
            exit(EXIT_FAILURE); 
        }
        case 0: {
            int file_std = open("/tmp/daemon.out", O_CREAT | O_WRONLY | O_TRUNC, 0644);
            int file_err = open("/tmp/daemon.err", O_CREAT | O_WRONLY | O_TRUNC, 0644);
            int file_dev = open("/dev/null", O_RDONLY);

            if (file_std == -1 || file_err == -1 || file_dev == -1) {
                printf("ERRNO: %d - %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
            }

            // Ejercicio 2.2 - 13
            if ((dup2(file_std, STDOUT_FILENO)) == -1)  // STDOUT_FILENO = 1
                return -1;
            if (dup2(file_err, STDERR_FILENO) == -1)    // STDERR_FILENO = 2
                return -1;
            if (dup2(file_dev, STDIN_FILENO) == -1)    // STDERR_FILENO = 2
                return -1;

            printf("    Hijo %i (padre: %i)\n", getpid(), getppid());
                        // (PID, PPID, PGID y SID). ver diap 2.3 - 9, 10, 11
            printf("    PID:    %d  - ID unico\n", getpid());
            printf("    PPID:   %d  - ID proceso que lo creo\n", getppid());
            printf("    PGID:   %d  - ID grupo de procesos\n", getpgid(getpid()));
            printf("    SID:    %d  - ID de la sesion\n", getsid(getppid()));
            
            // Ejecución de Programas. ver diap 2.3 - 18
            if (execvp(argv[1], &argv[1]) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            printf("El comando termino de ejecutarase\n");

            close(file_dev);
            close(file_std);
            close(file_err);
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