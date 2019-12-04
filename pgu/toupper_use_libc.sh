
as toupper_use_libc.s -o toupper_use_libc.o

LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -lc -o toupper_use_libc toupper_use_libc.o

