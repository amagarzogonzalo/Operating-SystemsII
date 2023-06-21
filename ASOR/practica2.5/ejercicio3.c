/** USO
CONSOLA 1:
    $ ./host localhost 3000
CONSOLA 2:
    $ ./client localhost 3000 <comando>
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
    if (argc < 4) {
        printf("Usage: %s <host> <port> <cmd>\n", argv[0]);
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

    printf("> Cliente conectado\n");

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    // ENVIO
    if ((err = sendto(sd, argv[3], sizeof(argv[3]), 0, result->ai_addr, result->ai_addrlen)) == -1) {
        perror("sendto(..)");
        exit(EXIT_FAILURE);
    }
    printf("> send: %s\n", argv[3]);

    // RECEPCION
    switch (*argv[3]) {
        case 't': 
        case 'd': {
            size_t size_msg = 128;
            int msg[size_msg];
            if ((c = recvfrom(sd, msg, size_msg, 0, (struct sockaddr *) &addr, &addrlen)) == -1) {
                perror("recvfrom(..)");
                exit(EXIT_FAILURE);
            }

            printf("> recv: %s\n", msg);
        } break;
        default: break;
    }

    // CERRAR SOCKET
    printf("> Desconexion\n");
    close(sd);

    return 0;
}