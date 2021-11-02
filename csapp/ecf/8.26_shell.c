/*
 * shell demo, which have job control, builtin command 'quit', and you can 
 * excute executable file with full pathname, for example: /bin/sleep 30,
 * /bin/ls, /bin/ps, /bin/date
 *
 */

/* $begin shellmain */
#include "../csapp.h"

#include <stdarg.h>

#define MAXARGS 128

#define MAXJOBS 10
#define MSGLEN 128

typedef enum {
    PS_RUNNING,
    PS_STOPPED,
    PS_TERMINATED
} job_state;

char *job_state_name[] = {
    "Running",
    "Stopped",
    "Terminated"
};

struct job {
    char *cmdline;
    int pid;
    int jid; /* job id */
    job_state state;
};

struct job jobs[MAXJOBS];


/* foregroud process group id */
volatile sig_atomic_t fgid = 0;

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 

void show_jobs();
void add_job(const char *cmdline, int pid, job_state state);
void remove_job(int pid);
void change_job_state(int pid, job_state state);
int get_pid_by_jid(int jid);

// Safe printf function
ssize_t Sio_printf(char *fmt, ...)
{
    char msg[MSGLEN];

    va_list args;
    va_start(args, fmt);
    /* there must use vsnprintf */
    vsnprintf(msg, MSGLEN, fmt, args);
    va_end(args);
    
    return write(STDOUT_FILENO, msg, strlen(msg));
}

void parent_handler(int sig)
{
    // if there is no foreground process group, then return
    if (fgid == 0)
        return;

    // kill foreground process
    Kill(-fgid, sig);

    if (sig == SIGINT) {
        Sio_printf("\nJob %d terminated by signal: %s\n",
                fgid, strsignal(sig));
    } else if (sig == SIGTSTP) {
        Sio_printf("\nJob %d stopped by signal: %s\n",
                fgid, strsignal(sig));
    }

    fgid = 0;
}


int main() 
{
    /* Install handlers for some signal */
    Signal(SIGINT, parent_handler);
    Signal(SIGTSTP, parent_handler);

    char cmdline[MAXLINE]; /* Command line */
    pid_t pid;
    int status;

    while (1) {
        /* Read */
        printf("> ");                   

        Fgets(cmdline, MAXLINE, stdin); 
        
        if (feof(stdin))
            exit(0);

        /* Evaluate */
        eval(cmdline);
        
        if ((pid = waitpid(-1, &status, WNOHANG|WUNTRACED|WCONTINUED)) > 0) {

            if (WIFEXITED(status)) {
                Sio_printf("Child %d exited normally, status: %d\n",
                        pid, WEXITSTATUS(status));
                remove_job(pid);

            } else if (WIFSIGNALED(status)) {
                Sio_printf("Child %d terminated by signal, signal: %s\n",
                        pid, strsignal(WTERMSIG(status)));
                change_job_state(pid, PS_TERMINATED);

            } else if (WIFSTOPPED(status)) {
                Sio_printf("Child %d stopped by signal, signal: %s\n",
                        pid, strsignal(WSTOPSIG(status)));
                change_job_state(pid, PS_STOPPED);

            } else if (WIFCONTINUED(status)) {
                Sio_printf("Child %d continued by signal\n" ,pid);
                change_job_state(pid, PS_RUNNING);
            }

        }
    } 
}
/* $end shellmain */


/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */

    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv); 

    if (argv[0] == NULL)  
        return;   /* Ignore empty lines */

    /* builtin command */
    if (builtin_command(argv)) { 
        return;
    }

    /* not builtin command */
    if ((pid = Fork()) == 0) {   /* Child runs user job */

        Signal(SIGINT, SIG_DFL);
        Signal(SIGTSTP, SIG_DFL);

        Setpgid(0, 0);

        /* printf("pid %d, ppid %d, pgid %d\n", getpid(),  */
                /* getppid(), getpgrp()); */
        if (execve(argv[0], argv, environ) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }

        return;
    }


    /* Parent waits for foreground job to terminate */
    int status;
    if (!bg) {

        fgid = pid;

        // Waiting for the foreground process to terminates
        if (Waitpid(pid, &status, WUNTRACED) > 0) {
            fgid = 0;
            if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTSTP) {

                // add process group to backgroud jobs, whose state is Stopped
                add_job(cmdline, pid, PS_STOPPED);
            }
        }

    } else {

        // add process group to backgroud jobs, whose state is Running
        add_job(cmdline, pid, PS_RUNNING);
    }

    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    /* quit command */
    if (!strcmp(argv[0], "quit"))
		exit(0);  

    /* show jobs */
    if (!strcmp(argv[0], "jobs"))
    {
        show_jobs();
        return 1;
    }

    /*
     * > bg %jid/pid
     * send SIGCONT to process which specified by jid/pid 
     */
    if (!strcmp(argv[0], "bg")) {

        int jid = 0, pid = 0;
        char c = *(argv[1]);

        if (c == '%') {
            if (strlen(argv[1]) >= 2) {
                jid = atoi(++argv[1]);
                if (jid > 0)
                    pid = get_pid_by_jid(jid);
            }
        } else {
            pid = atoi(argv[1]);
        }

        if (pid > 0)
            Kill(pid, SIGCONT);

        return 1;
    }

    if (!strcmp(argv[0], "fg")) {

        int jid = 0, pid = 0;
        char c = *(argv[1]);

        if (c == '%') {
            if (strlen(argv[1]) >= 2) {
                jid = atoi(++argv[1]);
                if (jid > 0)
                    pid = get_pid_by_jid(jid);
            }
        } else {
            pid = atoi(argv[1]);
        }

        if (pid > 0) {
            Kill(pid, SIGCONT);
            fgid = pid;
            remove_job(pid);
        }

        return 1;
    }

    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
		return 1;

    return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;

        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* Ignore spaces */
                buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}
/* $end parseline */



// Display all jobs
void show_jobs()
{
    int i;
    for (i = 0; i < MAXJOBS; ++i) {
        if (jobs[i].pid > 0)
            printf("[%d] %d %s \t %s\n", jobs[i].jid, jobs[i].pid,
                job_state_name[(int)jobs[i].state], jobs[i].cmdline);
    }
}

// Add a process group to backgroud jobs
void add_job(const char *cmdline, int pid, job_state state)
{
    // seek a empty entry in array
    int i, empty_index = -1;
    for (i = 0; i < MAXJOBS; ++i) {
        if (jobs[i].pid == 0) {
            empty_index = i;
            break;
        }
    }

    if (empty_index < 0) {
        unix_error("reached max job limit.");
    }

    /* allocate memory space for the copy of cmdline */
    size_t size = strlen(cmdline);
    char *cmdline_copy = (char *)malloc(size + 1);
    strncpy(cmdline_copy, cmdline, size);

    /* trip the tailing newline character */
    if (cmdline_copy[size-1] == '\n')
        cmdline_copy[size-1] = '\0';

    /* put relate info in job structure */
    jobs[empty_index].cmdline = cmdline_copy;
    jobs[empty_index].pid = pid;
    jobs[empty_index].jid = empty_index + 1;
    jobs[empty_index].state = state;

    /* print backgroud process group info */
    printf("[%d] %d %s\n", empty_index + 1, pid, cmdline_copy);

    ++empty_index;
}

// Modify job's processes state
void change_job_state(int pid, job_state state)
{
    if (pid <= 0)
        return;

    int i;
    for (i = 0; i < MAXJOBS; ++i) {
        if (jobs[i].pid == pid) {
            jobs[i].state = state;
            break;
        }
    }
}

// Remove job from jobs array
void remove_job(int pid)
{
    if (pid <= 0)
        return;

    int i;
    for (i = 0; i < MAXJOBS; ++i) {
        if (jobs[i].pid == pid) {
            
            free(jobs[i].cmdline);

            jobs[i].cmdline = NULL;
            jobs[i].pid = 0;
            jobs[i].jid = 0;

            break;
        }
    }
}

// Get process group id by job id
int get_pid_by_jid(int jid)
{
    
    int i;
    for (i = 0; i < MAXJOBS; ++i) {
        if (jobs[i].jid == jid) {
            return jobs[i].pid;
        }
    }

    return 0;
}

