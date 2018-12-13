CC = gcc
CFLAG = -Wall -lm

main.out: main.o somefile.o
	$(CC) main.o somefile.o -o main.out $(CFLAG)

main.o: main.c somefile.h
	$(CC) -c main.c -o main.o $(CFLAG)

somefile.o: somefile.c
	$(CC) -c somefile.c -o somefile.o $(CFLAG)

clean:
	@echo "cleaning"
	-rm main.out *.o
	@echo "clean completed"
