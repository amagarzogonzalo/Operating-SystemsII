#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>



#define NI_MAXHOST      1025
#define NI_MAXSERV      32
#define N_BUFFER        81

void handler (int signal){
    pid_t pid;
    pid = wait(NULL);
    printf("Proceso finalizado porque estaba en estado Zombie.\n");
}

int main(int argc, char **argv){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    struct addrinfo *result;
    int s;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = 0;
    hints.ai_family = AF_UNSPEC; // IPv4 o IPv6
    /*If  the  AI_PASSIVE  flag  is  specified in hints.ai_flags, and node is
    NULL,  then  the  returned  socket  addresses  will  be  suitable   for
    bind(2)ing  a  socket  that  will  accept(2) connections.*/
    hints.ai_socktype = AI_PASSIVE;

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    int sd = socket(result->ai_family, result->ai_socktype, 0);
    bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);
    listen(sd, 5); // backlog - 5 (por defecto)
    int clisd;
    struct sockaddr_un peer_addr;
    socklen_t peer_addr_size;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    char buf[N_BUFFER];
    ssize_t c;
    signal(SIGCHLD, handler);
    int status;

    while (1) {
        /* Accept and Fork
        El servidor acepta conexiones con accept() y crea un proceso/thread para
        procesar cada una*/
        clisd = accept(sd, (struct sockaddr *) &peer_addr, &peer_addr_size);
        pid_t pid;
        pid = fork();

        if(pid == 0){
            getnameinfo((struct sockaddr *) &peer_addr, peer_addr_size, host, NI_MAXHOST,
            serv, NI_MAXSERV, NI_NUMERICHOST);
            // NI_NUMERICHOST If set, then the numeric form of the hostname is returned.

            printf("Conexión desde host: %s serv: %s\n", host, serv);
            printf("Conexión en proceso %i\n", getpid());

            while (c = recv(clisd, buf, 80, 0)) { // Comprobar mensaje!
                send(clisd, buf, c, 0);
            }

            close(clisd);
        }
        else{
            pid = wait(&status);
            close(clisd);
            exit(EXIT_SUCCESS);
        }

        
    }
    return 0;
}
