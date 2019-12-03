
as -64 helloworld-lib.s -o helloworld-lib.o

ld -o helloworld-lib -m elf_x86_64 \
    -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    helloworld-lib.o -lc

