
# -lpthread 必须出现在csapp.c 后面，才能被静态链接
gcc -Wall sigint.c ../csapp.c -o sigint.out -lpthread

