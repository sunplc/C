
as count-chars.s -o count-chars.o

as write-newline.s -o write-newline.o

as integer2string.s -o integer2string.o

as conversion_program.s -o conversion_program.o

ld integer2string.o count-chars.o write-newline.o \
    conversion_program.o -o conversion_program
