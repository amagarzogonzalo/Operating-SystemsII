// STANDARD
#include <stdlib.h>
// PRINTS
#include <stdio.h>
// SIGNAL
#include <signal.h>
// ERROR EXIT
#include <errno.h>
// ALARMAS
#include <unistd.h>
#include <sys/time.h>


// Declarar variables globales como volatile
volatile int cancel = 0;

// Manejador
void handler (int signal){
    if(signal == SIGUSR1) cancel = 1;
}


int main (int argc, char ** argv) {

    if (argc != 2) {
        printf("Faltan los segundos.\n");
        exit(EXIT_FAILURE);
    } 
    // SIGUSR1: Señales de usuario.
    sigset_t sig; 
    sigemptyset(&sig); // Se fija el conjunto vacío.
	sigaddset(&sig, SIGUSR1); // Se añade la señal SIGUSR1.
    sigprocmask(SIG_UNBLOCK, &sig, NULL); // Elimina el conjunto sig (SIGUSR1) de señales bloqueadas.

    struct sigaction sigh;
    sigaction(SIGUSR1, NULL, &sigh); // Almacenar en sig el antiguo controlador de la señal
    sigh.sa_handler = handler; // Nuevo manejador para la señal; su valor es un puntero a la función void handler
    sigaction(SIGUSR1, &sigh, NULL); // Conoce el nuevo manejador de la señal
    int segundos = atoi(argv[1]); // Convertir a entero.

    // man 2 alarm, man 2 setitimer
    alarm(segundos);
    int i;
    for(i = 0; i <segundos && cancel == 0; i++){
        printf("Quedan %i segundos.\n", segundos -i);
        sleep(1);
    }
    // Haciendo esta llamada se podría mandar la señal SIGUSR1 al proceso y cancelar.
    // [cursoredes@localhost P3]$ kill -s SIGUSR1 25872


    if(cancel == 0){
        printf("Borrando el ejecutable.\n");
        unlink(argv[0]);
    }
    else
        printf ("Se ha cancelado el borrado con éxito.\n");
    

    return 0;
}