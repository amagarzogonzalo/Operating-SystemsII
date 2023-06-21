// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>
// SIGNAL
#include <signal.h>
// ERROR EXIT
#include <errno.h>

// Declarar variables globales como volatile
volatile int ints = 0;
volatile int stps = 0;

// Manejador
void handler (int signal){
    if(signal == SIGINT) ints++;
    if(signal == SIGTSTP) stps++;
}

int main () {
    /*
    SIGINT - ControlC
    SIGTSTP - ControlZ
    */
    struct sigaction sig;
    sigaction(SIGINT, NULL, &sig); // Almacenar en sig el antiguo controlador de la señal
    sig.sa_handler = handler; // Nuevo manejador para la señal; su valor es un puntero a la función void handler
    sigaction(SIGINT, &sig, NULL); // Conoce el nuevo manejador de la señal
    sigaction(SIGTSTP, NULL, &sig); 
    sig.sa_handler = handler;
    sigaction(SIGTSTP, &sig, NULL);

    sigset_t sigset;
    sigemptyset(&sigset);

    while((ints + stps) < 10){
        sigsuspend(&sigset);
        /*
        La máscara de señales bloqueadas se susstituye por set, conjunto vació, y el proceso 
        se suspende hasta que una señal que no este en la máscara, cualquiera, se produzca.
        Cuando se reciba la señal se ejecuta el manejador -> handler(signal).
        Siempre devuelve -1.
        */
    }
    printf("Cuenta de SIGINT: %i\n", ints);
    printf("Cuenta de SIGTSTP: %i\n", stps);
    return 0;
}