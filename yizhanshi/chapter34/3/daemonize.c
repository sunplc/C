#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void daemonize(void)
{
	pid_t pid;
	/*
	 * Become a session leader to lose controlling TTY.
	 */
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	} else if (pid != 0) {
		exit(0);
	}
	setsid();
	
	/*
	 * Change the current directory to the root.
	 */
	if (chdir("/") < 0) {
		perror("chdir");
		exit(1);
	}

	/*
	 * Attach file descriptors 0, 1 and 2 to /dev/null
	 */
	close(0);
	dup2(0, 1);
	dup2(0, 2);
}

int main()
{
	daemonize();
	while(1);

    return 0;
}

