/* $begin cpfile */
#include "../csapp.h"

#define MIN(x,y) ((x) < (y) ? (x) : (y))

/*
 * for test
 *
 * #define MAXBUF 50
 */

int main(int argc, char **argv) 
{
    int n;
    rio_t rio;
    char buf[MAXLINE];
	ssize_t nleft = MAXBUF;

    Rio_readinitb(&rio, STDIN_FILENO);
    while ((n = Rio_readlineb(&rio, buf, MIN(nleft, MAXBUF))) != 0){
		nleft -= n;
        if (nleft <= 0)
            break;
		Rio_writen(STDOUT_FILENO, buf, n);
	}

    /* $end cpfile */
    exit(0);
    /* $begin cpfile */
}
/* $end cpfile */



