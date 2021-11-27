#include "../csapp.h"


int dd2hex(char *dd, char *hex)
{
    char *seg, *ptr, *ptr_copy, *endptr;   
    seg = (char *)malloc(4);
    unsigned int ip = 0;
    int length = strlen(dd);
    ptr = (char *)malloc(length);
    ptr_copy = ptr;
    memcpy(ptr, dd, length);

    while ((endptr = strchr(ptr, '.')) != NULL) {
        length = endptr - ptr + 1;
        *endptr = '\0';
        seg = strncpy(seg, ptr, length);
        ptr = endptr + 1;
        ip = (ip << 8) + atoi(seg);
    }

    // get the last segment
    endptr = strchr(ptr, '\0');
    length = endptr - ptr + 1;
    seg = strncpy(seg, ptr, length);
    ip = (ip << 8) + atoi(seg);

    sprintf(hex, "0x%x", ip);

    free((void *)ptr_copy);
    free((void *)seg);

    return 0;
}
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
