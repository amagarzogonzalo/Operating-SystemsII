#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    if (setuid(2) == -1) {
        perror(strerror(3));
        return -1;
    }
    return 1;
}