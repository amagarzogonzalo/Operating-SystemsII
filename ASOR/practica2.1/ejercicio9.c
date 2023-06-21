#include <stdio.h>
#include <unistd.h>

int main() {
    printf("man id\n");
    printf("UID: %d\n", getuid());
    printf("EUID: %d\n", geteuid());

    return 0;
}