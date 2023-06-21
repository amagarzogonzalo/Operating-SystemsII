#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (){
    mode_t original = umask(027); 
	int openn = open("prueba7.txt", O_CREAT | O_RDONLY, 0777);
	mode_t nueva = umask(original);
	printf("Mostrar: %i\n", nueva);
	return 0;
}

/*
[cursoredes@localhost P2]$ gcc ejercicio7.c -o  ejercicio
[cursoredes@localhost P2]$ ./ejercicio 
Mostrar: 23
[cursoredes@localhost P2]$ ls -l
total 40
-rwxr-x--- 1 cursoredes cursoredes 8552 Nov 21 10:29 ejercicio
-rw-rw-r-- 1 cursoredes cursoredes  421 Nov 21 09:24 ejercicio1.c
-rw-rw-r-- 1 cursoredes cursoredes  250 Nov 21 09:30 ejercicio2.c
-rw-rw-r-- 1 cursoredes cursoredes  182 Nov 21 09:45 ejercicio3.c
-rw-rw-r-- 1 cursoredes cursoredes  392 Nov 21 09:45 ejercicio4.c
-rw-rw-r-- 1 cursoredes cursoredes  973 Nov 21 10:04 ejercicio5.c
-rw-rw-r-- 1 cursoredes cursoredes  812 Nov 21 10:28 ejercicio6.c
-rw-rw-r-- 1 cursoredes cursoredes  302 Nov 21 10:26 ejercicio7.c
-rwxr-x--- 1 cursoredes cursoredes    0 Nov 21 10:27 prueba7.txt


Este nuevo fichero se crea usando la mascara 027 por lo que se restringe escritura en
grupo y todo en otros.

*/