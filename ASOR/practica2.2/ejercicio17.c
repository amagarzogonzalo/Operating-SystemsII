// STANDARD LIB
#include <stdlib.h>
// I/O
#include <stdio.h>
// FILES
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// DIRS
#include <dirent.h>
// ERROR EXIT
#include <errno.h>
// CONSTANTS and LINKS
#include <unistd.h>


// Escribir un programa que muestre el contenido de un directorio
int main(int argc, char *argv[]) {
    // El programa tiene un único argumento que es la ruta a un directorio
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE); 
    }

    // Abrir un directorio indicado por argv[1]
    DIR *d = opendir(argv[1]);
    // El programa debe comprobar la corrección del argumento
    if (d == NULL) {
        perror("ERROR");
        return -1;
    }

    // El prog recorrera las entradas del directorio y escribira los nombres
    // Leer entradas de un directorio
    struct dirent *entry;

    int size = 0;
    while ((entry = readdir(d)) != NULL) {
        
        printf("%s", entry->d_name);
        // Si es un fichero regular y tiene permiso de ejecución
        if (entry->d_type == DT_REG && access(entry->d_name, X_OK)) {
            printf("*");
            size += entry->d_off;
        }
        else 
        // Si es un directorio
        if (entry->d_type == DT_DIR) {
            // Escribirá el carácter ‘/’ después del nombre
            printf("/");
        }
        else
        // Si es un enlace simbolico
        if (entry->d_type == DT_LNK ) {
            char* linked;
            readlink(entry->d_name, linked, _PC_NAME_MAX);
            printf(" -> %s, ");
        }
        printf("\n");
    }

    // Escribirá el tamaño total que ocupan los ficheros
    printf("REGULAR FILES SIZE: %d\n", size);

    // Cerrar el directorio, haciendolo inaccesible
    int err;
    if ((err = closedir(d)) == -1) {
        perror("closedir(..)");
        return -1;
    }

    return EXIT_SUCCESS;
}