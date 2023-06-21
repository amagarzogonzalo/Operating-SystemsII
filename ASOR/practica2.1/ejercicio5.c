#include <sys/utsname.h>
#include <errno.h>
#include <stdio.h>

int main() {
    struct utsname buf;

    if (uname(&buf) == -1) {
        printf("ERRNO %d - %s", errno, strerror(errno));
        return -1;
    }

    printf("man uname -a: %s\n", buf.sysname);
    printf("man uname -n: %s\n", buf.nodename);
    printf("man uname -r: %s\n", buf.release);
    printf("man uname -v: %s\n", buf.version);
    printf("man uname -m: %s\n", buf.machine);

    return 0;
}