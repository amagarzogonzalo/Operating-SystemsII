#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <unistd.h>


    int main(int argc, char *argv[]){
        struct stat sb;

        if (argc != 2) {
            fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        if (stat(argv[1], &sb) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        char* rig = malloc(sizeof(char)*(5 + strlen(argv[1])));
        strcpy(rig, argv[1]);
        rig = strcat(rig, ".hard");
        printf("Rigido: %s\n", rig);
        
        char* sim = malloc(sizeof(char)*(5 + strlen(argv[1])));
        strcpy(sim, argv[1]);
        sim = strcat(sim, ".sym");
        printf("Simbolico: %s\n", sim);

        if ((sb.st_mode & S_IFMT) == S_IFREG) {
               /* Handle regular file */
                printf("%s Handle regular file.\n", argv[1]);
                if(link(argv[1],rig) == -1) printf("Error al crear enlace rigido o duro. \n");
                else printf("Enlace rigido OK\n");
                if(symlink(argv[1],sim) == -1) printf("Error al crear enlace simbolico. \n");
                else printf("Enlace simbolico OK\n");

        }
        else printf("%s Not Handle regular file.\n", argv[1]);


        
    
        exit(EXIT_SUCCESS);
}

/*
[cursoredes@localhost P2]$ ./ejercicio ejercicio11.c
Rigido: ejercicio11.c.hard
Simbolico: ejercicio11.c.sym
ejercicio11.c Handle regular file.
Enlace rigido OK
Enlace simbolico OK

Se crean correctamente estos archivos;
Rigido: ejercicio11.c.hard
Simbolico: ejercicio11.c.sym
*/

