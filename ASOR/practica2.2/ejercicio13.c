// STANDARD LIB
#include <stdlib.h>
// I/O
#include <stdio.h>
// FILES
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// ERROR EXIT
#include <errno.h>
// CONSTANTS
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int file = open(argv[1], O_CREAT | O_RDWR, 00777);
    if (file == -1) {
        printf("ERRNO: %d - %s\n", errno, strerror(errno));
        return -1;
    }

    if ((dup2(file, STDOUT_FILENO)) == -1)  // STDOUT_FILENO = 1
        return -1;
    if (dup2(file, STDERR_FILENO) == -1)    // STDERR_FILENO = 2
        return -1;

    printf("Se ha reedirigido a %s\n", argv[1]);
    perror("._. ERROR?");

    close(file);

    return EXIT_SUCCESS;
}