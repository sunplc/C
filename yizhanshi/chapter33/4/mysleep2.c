/* 实现sleep函数 */
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void sig_alarm(int signo)
{
    /* nothing to do */
}

unsigned int mysleep(unsigned int nsecs)
{
    struct sigaction    newact, oldact;
    sigset_t            newmask, oldmask, suspmask;
    unsigned int        unslept;
    /* set our handler, save previous information */
    newact.sa_handler = sig_alarm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    /* block SIGALRM and save current signal mask */
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    alarm(nsecs);

    suspmask = oldmask;
    sigdelset(&suspmask, SIGALRM);      /* make sure SIGALRM isn't blocked */
    sigsuspend(&suspmask);              /* wait for any signal to be caught */

    /* some signal has been caught, SIGALRM is now blocked. */
    unslept = alarm(0);
    sigaction(SIGALRM, &oldact, NULL); /* reset previous action */

    /* reset signal mask, which unblocks SIGALRM */
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return unslept;
}

int main(void)
{
    int remain = 0;
    while(1) {
        remain = mysleep(2);
        printf("Two seconds passed, remaining seconds = %d\n", remain);
    }
	return 0;
}

