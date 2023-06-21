#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>



int main(int argc, char ** argv) {

    if (argc < 2) {
        printf("Falta la ruta del archivo.\n");
        return -1;
    }

    int fd = open(argv[1], O_CREAT | O_RDWR, 0777);
    
    if (fd == -1) {
        printf("Error al crear el fichero o abrirlo.\n");
        return -1;
    }

    /*Specifying 0 for  l_len  has  the
       special  meaning:  lock all bytes starting at the location speci‐
       fied by l_whence and l_start through to the end of file, no  mat‐
       ter how large the file grows.*/
    struct flock lock;
    lock.l_type = F_WRLCK; // write lock
    lock.l_whence = SEEK_SET; // start of the file
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();


    int l = fcntl(fd, F_GETLK, &lock);

    // comprobar que se puede poner lock con F_GETLK
    if(lock.l_type == F_UNLCK){ //ok
        printf("The lock could be placed.\n");
        lock.l_type = F_WRLCK; // se vuelve a activar F_WRLCK ya que fue cambiado
        int setl = fcntl(fd, F_SETLK, &lock);
        
        if (setl== -1) {
            printf("A conflicting lock is held by another process.\n");
            close(fd);
            return 1;
        } 
        printf("The lock is placed.\n");
        time_t tim = time(NULL);
        struct tm *tiempo = localtime(&tim);

        char buff[70];

        strftime(buff, 70, "%A, %d de %B %Y %H:%M", tiempo);

        printf("Fecha %s\n", buff);
        sleep(10);

        lock.l_type = F_UNLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        lock.l_pid = getpid();
        
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            printf("No se ha podido desbloquear.\n");
            close(fd);
            return 1;
        } 
        sleep(10);
        printf("Desbloqueo OK.\n");
        close(fd);
    }
    else {
        //printf3 tipos datos
        printf("El fichero se encontraba bloqueado por otro proceso: %d\n", lock.l_pid);
        close(fd);
        return 1;
    }
    return 0;

}