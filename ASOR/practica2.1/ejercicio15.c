#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>

int main(){
  char *string = setlocale(LC_ALL, "es_ES");
  if (string != NULL){
    time_t tim = time(NULL);
    struct tm *tiempo = localtime(&tim);

    char buff[70];

    strftime(buff, 70, "%A, %d de %B %Y %H:%M", tiempo);

    printf("Fecha %s\n", buff);
  }
  return 1;
}