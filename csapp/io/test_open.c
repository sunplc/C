#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    open("test_open.txt", O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);

    return 0;
}
