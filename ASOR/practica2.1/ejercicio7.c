#include <stdio.h>
#include <unistd.h>

int main() {
    printf("man pathconf\n");
    printf("LINK_MAX: %d\n", pathconf("/", _PC_LINK_MAX));
    printf("PATH_MAX: %d\n", pathconf("/", _PC_PATH_MAX));
    printf("NAME_MAX: %d\n", pathconf("/", _PC_NAME_MAX));

    return 0;
}