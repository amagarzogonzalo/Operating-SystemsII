#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

    int main(int argc, char *argv[]){
        struct stat sb;

        if (argc != 2) {
            fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        if (stat(argv[1], &sb) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        
        // printf(3) man para ver li es en decimal lx hexadecimal.
        printf("Major and Minor:  [%li,%li]\n",
                (long) major(sb.st_dev), (long) minor(sb.st_dev));

        printf("File type:                ");

        switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
        }
        printf("I-node number:            %ld\n", (long) sb.st_ino);

        printf("Last status change:       %s", ctime(&sb.st_ctime));
        printf("Last file modification:   %s", ctime(&sb.st_mtime));

        exit(EXIT_SUCCESS);
}

/*
[cursoredes@localhost P2]$ gcc ejercicio9.c -o  ejercicio
[cursoredes@localhost P2]$ ./ejercicio ejercicio9.c
Major and Minor:  [253,0]
File type:                regular file
I-node number:            3125630
Last status change:       Mon Nov 21 11:41:43 2022
Last file modification:   Mon Nov 21 11:41:43 2022
*/

