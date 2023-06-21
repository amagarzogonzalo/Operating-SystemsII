#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    if (setuid(2) == -1) {
        printf("ERRNO: %d - %s\n", errno, strerror(errno));
        return -1;
    }
    return 1;
}