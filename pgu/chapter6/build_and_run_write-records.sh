
make write-record.o
make read-record.o

ld -shared write-record.o read-record.o -o librecord.so

as write-records.s -o write-records.o

LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

ld -L . -lrecord \
    -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -o write-records write-records.o

# Do this if the above two line do not effect
# setenv LD_LIBRARY_PATH .

./write-records test.data

