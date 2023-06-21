#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


#define NI_MAXHOST      1025
#define NI_MAXSERV      32
#define N_BUFFER        81


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
    hints.ai_socktype = AI_PASSIVE;
    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    int sd = socket(result->ai_family, result->ai_socktype, 0);

    // Esquema a seguir en cliente: Socket(): Connect() -> Send () -> Recv() -> Close()
    // Diapo 18
    connect(sd, result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);
   
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    char buf[N_BUFFER];
    char bufentrada[N_BUFFER];

    ssize_t c;

    // Importante: sd tiene que ser el mismo para send recv y socket.
    while (1) {
        c = read(0,buf, 80);
        buf[c] = '\0';
        send(sd, buf, c, 0);
         
        if ((buf[0] == 'Q') && (c == 2)) {
            printf("Conexión terminada.\n");
            break;
        }
        c = recv(sd, bufentrada, 80, 0);
        bufentrada[c] = '\0';
        printf("%s\n", bufentrada);
        

    }

    close(sd);

    return 0;
}