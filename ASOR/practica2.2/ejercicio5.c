#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (){
    // 110 100 101 + un 0 es predecido por un 0.
    int x = open("/home/cursoredes/Documents/P2/prueba5.txt", O_CREAT, 0645);
    printf("Descriptor fichero %i\n", x);
    return 1;
}


/*
[cursoredes@localhost P2]$ gcc ejercicio5.c -o  ejercicio
[cursoredes@localhost P2]$ ./ejercicio 
[cursoredes@localhost P2]$ ./ejercicio 
Descriptor fichero 3


[cursoredes@localhost P2]$ ls -l
total 32
-rwxrwxr-x 1 cursoredes cursoredes 8496 Nov 21 10:03 ejercicio
-rw-rw-r-- 1 cursoredes cursoredes  421 Nov 21 09:24 ejercicio1.c
-rw-rw-r-- 1 cursoredes cursoredes  250 Nov 21 09:30 ejercicio2.c
-rw-rw-r-- 1 cursoredes cursoredes  182 Nov 21 09:45 ejercicio3.c
-rw-rw-r-- 1 cursoredes cursoredes  392 Nov 21 09:45 ejercicio4.c
-rw-rw-r-- 1 cursoredes cursoredes  303 Nov 21 10:03 ejercicio5.c
-rw-r--r-x 1 cursoredes cursoredes    0 Nov 21 10:03 prueba5.txt

*/
