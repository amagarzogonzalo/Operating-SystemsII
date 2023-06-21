// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>

int main (int argc, char *argv[]) {
    
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <command> <options>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Ejecución de Programas. ver diap 2.3 - 19
    if (system(*(argv + 1)) != 0) {
        perror("system");
        exit(EXIT_FAILURE);
    }
    printf("El comando termino de ejecutarase\n");

    return EXIT_SUCCESS;
}