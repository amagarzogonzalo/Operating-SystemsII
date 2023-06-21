#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main (){
    //time()  returns  the  time  as  the  number of seconds since the
    // Epoch, 1970-01-01 00:00:00 +0000 (UTC).


    time_t tim = time(NULL);
    printf("Time: %d\n", tim);


    return 0;
}