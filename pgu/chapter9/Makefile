
LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

read-records: count-chars.o write-newline.o read-record.o \
	read-records.o
	ld -lc -m elf_x86_64 \
    -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
		count-chars.o write-newline.o read-record.o \
		read-records.o -o read-records

read-record.o: read-record.s linux.s record-def.s
	as read-record.s -o read-record.o

count-chars.o: count-chars.s
	as count-chars.s -o count-chars.o

write-newline.o: write-newline.s linux.s
	as write-newline.s -o write-newline.o

read-records.o: read-records.s linux.s record-def.s alloc.s
	as read-records.s -o read-records.o

