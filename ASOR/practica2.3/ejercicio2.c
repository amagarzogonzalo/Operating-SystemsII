#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv){

    int sched = sched_getscheduler(getpid());
    switch(sched){
        case 0: printf("Sched: Other.\n");
        break;
        case 1: printf("Sched: FIFO.\n");
        break;
        case 2:printf("Sched: Round Robin.\n");
        break;
    }
    int max = sched_get_priority_max(sched);
    int min = sched_get_priority_min(sched);
    printf("Valor Maximo: %d.\n", max);
    printf("Valor Minimo: %d.\n", min);

    struct sched_param par;
    sched_getparam(getpid(), &par);
    printf("Prioridad %d.\n", par.__sched_priority);

    
    return 0;
}

