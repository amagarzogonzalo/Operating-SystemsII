#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




 int main(int argc, char *argv[]){

        if (argc != 2) {
            fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        int desc = open(argv[1], O_CREAT | O_RDWR, 00777);
        if (desc == -1) {
            return -1;
        }         
        int desc2 = dup2(desc, 1);
        printf("Se ha reedirigido a %s\n", argv[1]);
        dup2(desc2, desc);
        return 0;
 }

 /*
[cursoredes@localhost P2]$ gcc ejercicio12.c -o ejercicio
[cursoredes@localhost P2]$ ./ejercicio prueba12.txt
[cursoredes@localhost P2]$ cat prueba12.txt
Se ha reedirigido a prueba12.txt
 */