main: main.o stack.o maze.o
	gcc main.o stack.o maze.o -o main

main.o maze.o stack.o: main.h
stack.o main.o: stack.h
maze.o main.o: maze.h

clean:
	@echo "cleanning project"
	-rm main *.o
	@echo "clean completed"

.PHONY: clean
