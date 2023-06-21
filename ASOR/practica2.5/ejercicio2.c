/** USO
CONSOLA 1:
    $ ./host localhost 3000
CONSOLA 2:
    $ nc -l localhost 3000
*/

// STANDARD
#include <stdlib.h>
// I/O
#include <stdio.h>
// ADDRESS
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
// TIME
#include <time.h>

int main(int argc, char *argv[]) {
    // La dirección y el puerto son el primer y segundo argumento del programa
    if (argc < 3) {
        printf("Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    struct addrinfo *result;

    // Plantilla de UDP. ver diap. 2.4 - 16
    hints.ai_flags    = AI_PASSIVE;
    hints.ai_family   = AF_UNSPEC;   // IPv4 o IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = 0;

    int rc, sd, bd, c, err;

    if ((rc = getaddrinfo(argv[1], argv[2], &hints, &result)) < 0) {
        perror("getaddrinfo(..)");
        exit(EXIT_FAILURE);
    }

    // CREACION DEL SOCKET
    if ((sd = socket(result->ai_family, result->ai_socktype, 0)) == -1) {
        perror("socket(..)");
        exit(EXIT_FAILURE);
    }

    // ASOCIAR DIRECCION
    if ((bd = bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen)) == -1) {
        perror("bind(..)");
        exit(EXIT_FAILURE);
    }

    printf("Host abierto\n");

    char buf[2];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    // COMUNICACION
    do {
        struct sockaddr_storage addr;
        socklen_t addrlen = sizeof(addr);

        if ((c = recvfrom(sd, buf, 2, 0, (struct sockaddr *) &addr, &addrlen)) == -1) {
            perror("recvfrom(..)");
            exit(EXIT_SUCCESS);
        }

        if ((err = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV)) < 0) {
            perror("getnameinfo(..)");
            exit(EXIT_FAILURE);
        }

        printf("%d bytes de %s:%s\n", c, host, serv);

        // ref: https://stackoverflow.com/questions/5141960/get-the-current-time-in-c
        time_t rawtime = time(&rawtime);
        struct tm *timeinfo = localtime(&rawtime);
        size_t size_msg = 128;
        char msg[size_msg];

        switch (buf[0]) {
            case 't': 
            case 'd': {
                size_t strf;
                if (buf[0] == 't')
                    strf = strftime(msg, size_msg, "%T", timeinfo);
                else  strf = strftime(msg, size_msg, "%F", timeinfo);

                if ((err = sendto(sd, msg, strf, 0, (struct sockaddr *) &addr, addrlen)) == -1) {
                    perror("sendto(..)");
                    exit(EXIT_FAILURE);
                }
            } break;
            case 'q': {
                printf("Saliendo\n");
            } break;
            default: {
                printf("ERROR: cmd\n");
            } break;
        }

        sendto(sd, buf, c, 0, (struct sockaddr *) &addr, addrlen);
    } while (buf[0] != 'q');

    // CERRAR SOCKET
    close(sd);

    return 0;
}