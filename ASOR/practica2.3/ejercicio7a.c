// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>

int main (int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Ejecución de Programas. ver diap 2.3 - 18
    if (execvp(argv[1], &argv[1]) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    printf("El comando termino de ejecutarase\n");

    return EXIT_SUCCESS;
}