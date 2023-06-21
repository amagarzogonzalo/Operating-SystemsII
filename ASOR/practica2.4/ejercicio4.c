#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


// Manual mkfifo 3

int main(int argc, char **argv){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char pipe [] = "/home/cursoredes/Documents/P4/pipe";
    printf("HOME: %s\n", pipe);
  	mkfifo(pipe, 0777); 

    int fd = open(pipe, O_WRONLY);
    write(fd, argv[1], strlen(argv[1]));
    close(fd);

    return 0;
}

/*
En un terminal:
[cursoredes@localhost P4]$ ./ejercicio4 Prueba12344
HOME: /home/cursoredes/Documents/P4/pipe

En un segundo terminal:
[cursoredes@localhost P4]$ cat pipe
Prueba12344
*/