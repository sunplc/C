
make write-record.o
make read-record.o

ld -shared write-record.o read-record.o -o librecord.so

as write-records.s -o write-records.o

ld -L . -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -o write-records -lrecord write-records.o

LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

# Do this if the above two line do not effect
# setenv LD_LIBRARY_PATH .

./write-records test.data

