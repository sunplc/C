
as -64  setx.s -o setx.o

ld -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -lc setx.o -o setx.out

