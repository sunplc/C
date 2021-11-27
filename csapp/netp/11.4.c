#include "../csapp.h"

int main(int argc, char **argv) 
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc;

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));                         

    hints.ai_family = AF_INET;       /* IPv4 only */        //line:netp:hostinfo:family
    hints.ai_socktype = SOCK_STREAM; /* Connections only */ //line:netp:hostinfo:socktype

    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    struct sockaddr_in *sockp;
    /* Walk the list and display each IP address */
    for (p = listp; p; p = p->ai_next) {
        sockp = (struct sockaddr_in *)p->ai_addr;
        inet_ntop(AF_INET, &(sockp->sin_addr), buf, MAXLINE);
        printf("%s\n", buf);
    } 

    /* Clean up */
    Freeaddrinfo(listp);

    exit(0);
}
/* $end hostinfo */
