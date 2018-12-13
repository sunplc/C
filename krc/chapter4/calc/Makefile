CC = gcc
CFLAG = -Wall -lm

main.out: main.o getch.o getop.o stack.o
	$(CC) main.o getch.o getop.o stack.o -o main.out $(CFLAG)

clean:
	@echo "cleaning"
	-rm main.out *.o
	@echo "clean completed"
