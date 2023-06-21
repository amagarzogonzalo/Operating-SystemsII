#include <stdio.h>
#include <unistd.h>

int main() {
    printf("man sysconf\n");
    printf("ARG_MAX: %d\n", sysconf(_SC_ARG_MAX));
    printf("CHILD_MAX: %d\n", sysconf(_SC_CHILD_MAX));
    printf("OPEN_MAX: %d\n", sysconf(_SC_OPEN_MAX));

    return 0;
}
