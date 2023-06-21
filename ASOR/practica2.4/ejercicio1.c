#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define P_WRITE 1
#define P_READ 0

// paginas Manual: fork 2, pipe 2 (plantilla), dup 2

int main (int argc, char ** argv){
    int pipefd[2]; // Extremo de escritura fd[1] y lecutra fd[0]
    pid_t cpid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Hijo de tubería y ejecuta com2 arg2 */
        dup2(pipefd[P_READ], 0); // Redirecciona entrada estándar al extremo de lectura
        close(pipefd[P_WRITE]);          /* Close unused write end */
        close(pipefd[P_READ]);
        execlp(argv[3], argv[3], argv[4], (char*)NULL); // tiene que terminar con un Nulo
        _exit(EXIT_SUCCESS);
    }
    else { /* Padre  de tubería y ejecuta com1 arg1*/
        dup2(pipefd[P_WRITE], 1); // Redirecciona salida estándar al extremo de escritura
        close(pipefd[P_READ]);          /* Close unused read end */
        close(pipefd[P_WRITE]);       /* Reader will see EOF */
        execlp(argv[1], argv[1], argv[2], (char*)NULL);
        exit(EXIT_SUCCESS);
    }
}