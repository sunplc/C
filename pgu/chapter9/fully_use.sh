
LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

as fully_use.s -o fully_use.o

ld -m elf_x86_64 -lc \
    -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    fully_use.o -o fully_use

