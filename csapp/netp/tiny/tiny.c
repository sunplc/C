/* 
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the 
 *     GET method to serve static and dynamic content.
 *
 * Updated 11/2019 droh 
 *   - Fixed sprintf() aliasing issue in serve_static(), and clienterror().
 */
#include "../../csapp.h"

void doit(int fd);
void read_request(rio_t *rp, char *content_type, size_t, char *, size_t);
int parse_uri(char *uri, char *filename, char *cgiargs);
void get_filetype(char *filename, char *filetype);
void serve_static(int fd, char *method, char *filename, int filesize);
void serve_dynamic(int fd, char *method, char *filename, char *cgiargs);
void clienterror(int fd, char *method, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);


/* My rio_writen, if caught EPIPE erro, return -1 */
int My_rio_writen(int fd, void *usrbuf, size_t n) {
    int rc;
    if ( (rc = rio_writen(fd, usrbuf, n)) != n) {
        if (errno == EPIPE)
            fprintf(stderr, "EPIPE error\n");

        fprintf(stderr, "%s\n", strerror(errno));
    }

    return rc;
}

/*
 * signal SIGPIPE handler
 */
void sigpipe_handler(int sig)
{
    Sio_puts("SIGPIPE Caught\n");
}

/*
 * signal SIGCHLD handler
 */
void sigchld_handler(int sig)
{
    int olderrno = errno;
    while (waitpid(-1, NULL, 0) > 0) {
        /* Sio_puts("Child terminated\n"); */
    }
    
    if (errno != ECHILD) {
        Sio_error("Waitpid error");
    }
    errno = olderrno;
}


int main(int argc, char **argv) 
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    Signal(SIGPIPE, sigpipe_handler);
    Signal(SIGCHLD, sigchld_handler);

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
                    port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        doit(connfd);
        Close(connfd);
        printf("Connection Closed: fd %d\n", connfd);
    }
}
/* $end tinymain */

/*
 * doit - handle one HTTP request/response transaction
 */
/* $begin doit */
void doit(int fd) 
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE], content_type[MAXLINE], body[MAXLINE];
    rio_t rio;

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE))
        return;

    // print the request-line
    printf("%s", buf);

    sscanf(buf, "%s %s %s", method, uri, version);

    if (strcasecmp(method, "GET") 
        && strcasecmp(method, "POST")
        && strcasecmp(method, "HEAD")) {
        clienterror(fd, method, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }

    read_request(&rio, content_type, MAXLINE-1, body, MAXLINE-1);

    /* Parse URI from request */
    is_static = parse_uri(uri, filename, cgiargs);

    // printf("is_static=%d\n", is_static);

    if (!strcasecmp(content_type, "application/x-www-form-urlencoded")) {
        strncpy(cgiargs, body, MAXLINE-1);
    }

    // printf("cgiargs=%s\n", cgiargs);

    if (stat(filename, &sbuf) < 0) {
        clienterror(fd, method, filename, "404", "Not found",
		    "Tiny couldn't find this file");
        return;
    }

    if (is_static) { /* Serve static content */          
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            clienterror(fd, method, filename, "403", "Forbidden",
                "Tiny couldn't read the file");
            return;
        }
        serve_static(fd, method, filename, sbuf.st_size);
    }
    else { /* Serve dynamic content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
            clienterror(fd, method, filename, "403", "Forbidden",
                "Tiny couldn't run the CGI program");
            return;
        }
        serve_dynamic(fd, method, filename, cgiargs);
    }
}
/* $end doit */

/*
 * read_requesthdrs - read HTTP request headers
 */
/* $begin read_requesthdrs */
void read_request(rio_t *rp, char *content_type, size_t content_type_len, char *body, size_t body_len) 
{
    char buf[MAXLINE];
    int content_length = 0, rc;
    char *p;

    Rio_readlineb(rp, buf, MAXLINE);
    // printf("%s", buf);
    while (strcmp(buf, "\r\n")) {
        if ((rc = Rio_readlineb(rp, buf, MAXLINE)) <= 0) {
            // printf("rc=%d\n", rc);
            break;
        }

        if (strcasestr(buf, "Content-Type")) {
            p = strchr(buf, ':');
            if (p) {
                ++p;
                // trim the leading ' ' characters.
                while (*p == ' ')
                    ++p;
                strncpy(content_type, p, content_type_len);
                // trim the tailing '\r' and '\n' characters.
                if ((p = strchr(content_type, '\r'))) {
                    *p = '\0';
                }

                printf("Read: Content-Type:%s\n", content_type);
            }
        }

        if (strcasestr(buf, "Content-Length")) {
            p = strchr(buf, ':');
            if (p) {
                ++p;
                while (*p == ' ')
                    ++p;
                content_length = atoi(p);
                printf("Read: Content-Length:%d\n", content_length);
            }
        }

    }

    // printf("content_length=%d\n", content_length);

    // read the message-body
    if (content_length > 0) {
        Rio_readlineb(rp, body, content_length + 1);
    }

    return;
}
/* $end read_requesthdrs */

/*
 * parse_uri - parse URI into filename and CGI args
 *             return 0 if dynamic content, 1 if static
 */
/* $begin parse_uri */
int parse_uri(char *uri, char *filename, char *cgiargs) 
{
    char *ptr;

    if (!strstr(uri, "cgi-bin")) {  /* Static content */ //line:netp:parseuri:isstatic
        strcpy(cgiargs, "");                             //line:netp:parseuri:clearcgi
        strcpy(filename, ".");                           //line:netp:parseuri:beginconvert1
        strcat(filename, uri);                           //line:netp:parseuri:endconvert1
        if (uri[strlen(uri)-1] == '/')                   //line:netp:parseuri:slashcheck
	        strcat(filename, "home.html");               //line:netp:parseuri:appenddefault
        return 1;
    }
    else {  /* Dynamic content */                        //line:netp:parseuri:isdynamic

        ptr = index(uri, '?');                           //line:netp:parseuri:beginextract
        if (ptr) {
            strcpy(cgiargs, ptr+1);
            *ptr = '\0';
        }
        else 
            strcpy(cgiargs, "");                         //line:netp:parseuri:endextract

        strcpy(filename, ".");                           //line:netp:parseuri:beginconvert2
        strcat(filename, uri);                           //line:netp:parseuri:endconvert2
        return 0;
    }
}
/* $end parse_uri */

/*
 * serve_static - copy a file back to the client 
 */
/* $begin serve_static */
void serve_static(int fd, char *method, char *filename, int filesize)
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];

    /* Send response headers to client */
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n"
        "Server: Tiny Web Server\r\n"
        "Content-length: %d\r\n"
        "Content-type: %s\r\n\r\n", filesize, filetype);
        
    if (My_rio_writen(fd, buf, strlen(buf)) < 0) {
        return;
    }

    // for HTTP HEAD request, do not response message-body
    if (!strcasecmp(method, "HEAD")) {
        return;
    }

    /* Send response body to client, use mmap to map file to memory */
    // srcfd = Open(filename, O_RDONLY, 0);
    // srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    // Close(srcfd);
    // Rio_writen(fd, srcp, filesize);
    // Munmap(srcp, filesize);

    /* Send response body to client, use Rio_readn to read requested file */
    srcfd = Open(filename, O_RDONLY, 0);
    size_t readlen = 1024;
    srcp = (char *)Malloc(readlen);
    ssize_t nbytes;
    while ((nbytes = Rio_readn(srcfd, srcp, readlen - 1)) > 0) {
        if (My_rio_writen(fd, srcp, nbytes) < 0) {
            return;
        }
    }
    Close(srcfd);
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) 
{
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
        strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else if (strstr(filename, ".mp4"))
        strcpy(filetype, "video/mp4");
    else
        strcpy(filetype, "text/plain");
}  
/* $end serve_static */

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
/* $begin serve_dynamic */
void serve_dynamic(int fd, char *method, char *filename, char *cgiargs) 
{
    char buf[MAXLINE], *emptylist[] = { NULL };

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n"
        "Server: Tiny Web Server\r\n");
    if (My_rio_writen(fd, buf, strlen(buf)) < 0) {
        return;
    }
  
    // for HTTP HEAD request, do not response message-body
    if (!strcasecmp(method, "HEAD")) {
        return;
    }

    if (Fork() == 0) { /* Child */
        /* Real server would set all CGI vars here */
        setenv("QUERY_STRING", cgiargs, 1);
        Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */
        Execve(filename, emptylist, environ); /* Run CGI program */
    }
    // Wait(NULL); /* Parent waits for and reaps child */
}
/* $end serve_dynamic */

/*
 * clienterror - returns an error message to the client
 */
/* $begin clienterror */
void clienterror(int fd, char *method, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE];

    /* Print the HTTP response headers */
    sprintf(buf, "HTTP/1.0 %s %s\r\n"
        "Content-type: text/html\r\n\r\n", errnum, shortmsg);
    if (My_rio_writen(fd, buf, strlen(buf)) < 0) {
        return;
    }

    // for HTTP HEAD request, do not response message-body
    if (!strcasecmp(method, "HEAD")) {
        return;
    }

    /* Print the HTTP response body */
    sprintf(buf, "<html><title>Tiny Error</title>"
        "<body bgcolor=""ffffff"">"
        "%s: %s"
        "<p>%s: %s</p>"
        "<hr><em>The Tiny Web server</em>",
        errnum, shortmsg, longmsg, cause);
    if (My_rio_writen(fd, buf, strlen(buf)) < 0) {
        return;
    }
}
/* $end clienterror */
