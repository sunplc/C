
as -64  address.s -o address.o

ld -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -lc address.o -o address

