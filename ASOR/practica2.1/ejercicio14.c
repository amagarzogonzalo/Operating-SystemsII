#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main (){

    time_t tim = time(NULL);
    struct tm *t = localtime (&tim);

    int year = t->tm_year;
    year += 1900;
    printf("Year: %d\n", year);

    return 0;
}