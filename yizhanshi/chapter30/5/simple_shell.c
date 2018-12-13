#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define MAXLINE 80

void str_to_argv(char *command, char **av, int maxLen);
void remove_array_element(char **arr, int index, int len);

//int main(int argc, char *argv[], char * const envp[])
int main(int argc, char *argv[], char * envp[])
{
    write(STDOUT_FILENO, ">>> ", 4); //输出命令提示符
    char line[MAXLINE];
    int n;
    n = read(STDIN_FILENO, line, MAXLINE);
    if (n > 1) {
        char *command;
        command = line;

        int maxLen = 10; //最多接收10个参数
        char *myargv[maxLen];
        str_to_argv(command, myargv, maxLen);

        int i;
        char *one;
        //int has_pipe = 0;
        for (i=0; i < maxLen; i++) {
            if (myargv[i] != NULL) {
                one = myargv[i];
                if (one[0] == '>') {
                    remove_array_element(myargv, i, maxLen);
                    --i;
                    char *outputfile = strtok(one, ">");
                    //printf("output file is: %s\n", outputfile);
                    int fd = open(outputfile, O_RDWR|O_CREAT);
                    if (fd < 0) {
                        perror("open outputfile");
                        exit(1);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                } else if (one[0] == '<') {
                    remove_array_element(myargv, i, maxLen);
                    --i;
                    char *outputfile = strtok(one, "<");
                    int fd = open(outputfile, O_RDONLY);
                    if (fd < 0) {
                        perror("open");
                        exit(1);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                } else if (one[0] == '|') {
                    //has_pipe   = 1;
                }
                //printf("%d: %s\n", i, one);
            } else {
                break;
            }
        }
       
        execvp(command, myargv);
        perror("execlp");
    } else {
        printf("Command is too short.\n");
    }
    return 0;
}

void str_to_argv(char *command, char **myargv, int maxLen)
{
    char *token, *str, *saveptr;

    int i = 0;
    for (str = command; token != NULL; str = NULL) {
        if (i >= maxLen)
            break;
        token = strtok_r(str, " ", &saveptr);
        token = strtok(token, "\n");
        myargv[i] = token;
        ++i;
    }
}

void remove_array_element(char **arr, int index, int len)
{
    int i;
    for (i = index; i < len - 1; i++) {
        arr[i] = arr[i+1];
    }
}

