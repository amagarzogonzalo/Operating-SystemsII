#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// Solo se llega hasta el errno 133, el resto son desconocidos
int main() {
    int i = 0; 
    while (i < 255) {
        printf("ERRNO: %d - %s\n", i, strerror(i));
         ++i;
    }
    return 1;
}