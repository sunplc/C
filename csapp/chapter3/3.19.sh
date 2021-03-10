
as -64  3.19.s -o 3.19.o

ld -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -lc 3.19.o -o 3.19

