#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    printf("UID: %d\n", getuid());
    printf("EUID: %d\n", geteuid());

    struct passwd *buf = getpwuid(getuid());
    
    printf("id -n: %d\n", buf->pw_name);
    printf("direccion: %d\n", buf->pw_dir);
    printf("descripcion: %d\n", buf->pw_gecos);

    return 0;
}