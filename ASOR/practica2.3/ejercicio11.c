/** IMPORTANTE:
 * Se debe configurar la variable de entorno antes de ejecutar o
 * el programa no detectara la variable SLEEP_SECS. Esto se hace:
 * $ export SLEEP_SECS={number}
 * $ echo $SLEEP_SECS
*/

// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>
// SIGNAL
#include <signal.h>
// ERROR EXIT
#include <errno.h>

int main (int argc, char *argv[]) {

    // Plantilla signals. ver diap 2.3 - 15
    sigset_t blk_set;
    // Bloquear las señales SIGINT y SIGTSTP. ver diap 2.3 - 28
    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);    /* Ctrl+C */
    sigaddset(&blk_set, SIGTSTP);   /* Ctrl+Z */

    sigprocmask(SIG_BLOCK, &blk_set, NULL);

    // Conseguir las variables del entorno SLEEP_SECS. ver diap 2.3 - 13
    char *env;
    if ((env = getenv("SLEEP_SECS")) == NULL) {
        perror("getenv(SLEEP_SECS)");
        exit(EXIT_FAILURE);
    }
    sleep(atoi(env));

    // Al terminar debe comprobar si le llegaron las senales
    if (sigpending(&blk_set) == -1) {
        perror("sigpending");
        exit(EXIT_FAILURE);
    }

    // Informar de si recibio la senal SIGINT
    if (sigismember(&blk_set, SIGINT) == -1) {
        perror("sigismember - SIGINT");
        exit(EXIT_FAILURE);
    }
    // Informar de si recibio la senal SIGTSTP
    if (sigismember(&blk_set, SIGTSTP) == -1) {
        perror("sigismember - SIGTSTP");
        exit(EXIT_FAILURE);
    }

    // Desbloquearla
    if (sigprocmask(SIG_UNBLOCK, &blk_set, &blk_set) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("EXIT SUCCESS\n");

    return EXIT_SUCCESS;
}