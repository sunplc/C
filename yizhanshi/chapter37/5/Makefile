CFLAGS = -Wall

server: server.o wrap.o
	gcc server.o wrap.o -o server $(CFLAGS)

server.o: server.c wrap.h
	gcc -c server.c $(CFLAGS)

wrap.o: wrap.c
	gcc -c wrap.c $(CFLAGS)

clean:
	@echo "# cleaning project"
	-rm server *.o
	@echo "# clean completed"

.PHONY: clean
