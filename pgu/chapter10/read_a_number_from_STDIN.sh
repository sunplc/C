
as read_a_number_from_STDIN.s -o read_a_number_from_STDIN.o

LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

ld -L . -lc \
    -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -o read_a_number_from_STDIN  \
    read_a_number_from_STDIN.o
