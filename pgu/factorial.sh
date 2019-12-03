#! /bin/bash

as factorial_func.s -o factorial_func.o

ld -fPIC -shared factorial_func.o -o libfactorial.so

as factorial.s -o factorial.o

LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -L . -lc -lfactorial -o factorial factorial.o

