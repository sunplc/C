/*

3.71 ◆
Write a function good_echo that reads a line from standard input and writes it to
standard output. Your implementation should work for an input line of arbitrary
length. You may use the library function fgets, but you must make sure your
function works correctly even when the input line requires more space than you
have allocated for your buffer. Your code should also check for error conditions
and return when one is encountered.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 7  // defined a small SIZE for easy test

void good_echo(void)
{
    size_t len = SIZE;      // the length of buf
    char *buf = malloc(len);// buffer that used to store input line

    ssize_t n = 0, read_count = 0, write_count = 0;

    while ((n = read(STDIN_FILENO, buf + read_count, len - read_count - 1))) {
        read_count += n;

        // if the last readed char is '\n', just finish read
        if (buf[read_count - 1] == '\n')
            break;

        if (read_count == len - 1) {
            len += SIZE;
            buf = realloc(buf, len);

            if (buf == NULL) {
                perror("realloc failed:");
            }

        } else {
            break;
        }
    }

    buf[read_count] = '\0';

    write_count = write(STDOUT_FILENO, buf, read_count);

    printf("\n\nlength of read is %ld, length of write is %ld\n", read_count, write_count);
}

int main(void)
{
    good_echo();

    return 0;
}
