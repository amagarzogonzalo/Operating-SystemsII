#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main (){

    struct timeval tv;
    int primcuenta = gettimeofday(&tv, NULL);
    int inicio = tv.tv_usec;

    int i;
    for (i = 0; i < 1000000; i++){
    }

    int segcuenta = gettimeofday(&tv, NULL);
    int final = tv.tv_usec;

    printf("Inicio: %d\n", inicio);
    printf("Final: %d\n", final);
    int duracion = final - inicio;
    printf("Duracion: %d\n", duracion);

    return 0;
}