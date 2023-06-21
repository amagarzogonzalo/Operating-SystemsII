// STANDARD
#include <stdlib.h>
// GETADDRINFO
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
// MANUAL
#include <stdio.h>
#include <unistd.h>
#include <string.h>
// CONVERT IP
#include <arpa/inet.h>

 
#define BUF_SIZE 500
 
int main(int argc, char **argv) {
    struct addrinfo *result, *rp;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s ip\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0; /* Any */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    int s = getaddrinfo(argv[1], NULL, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    /*
        getaddrinfo() returns a list of address structures. Try each address until we
        successfully bind(2). If socket(2) (or bind(2)) fails, we (close the socket and)
        try the next address.
    */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        switch (rp->ai_family) {
            case AF_INET: {
                struct sockaddr_in *info = rp->ai_addr;
                char ip[INET_ADDRSTRLEN + 1]="";
                inet_ntop(AF_INET, &(info->sin_addr), ip, INET_ADDRSTRLEN + 1);
				printf("%s\t",ip);

            } break;
            case AF_INET6: {
                struct sockaddr_in6 *info6 = rp->ai_addr;
                char ipv6[INET6_ADDRSTRLEN + 1]="";
                inet_ntop(AF_INET6, &(info6->sin6_addr), ipv6, INET6_ADDRSTRLEN + 1); // convert IPv4 and IPv6 addresses from binary to text form
                printf("%s\t",ipv6);
        
            } break;
            default: {
                printf("Error getaddrinfo(): Name or service not known.\n");
            }
        }
        printf("%i\t%i\n",rp->ai_family, rp->ai_socktype);
    }

    freeaddrinfo(result);           /* No longer needed */  
    return 0;
}
