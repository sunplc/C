CFLAGS = -Wall

all: server client
.PHONY: all

server: server.o wrap.o
	gcc server.o wrap.o -o server $(CFLAGS)

client: client.o wrap.o
	gcc client.o wrap.o -o client $(CFLAGS)

server.o: server.c wrap.h
	gcc -c server.c $(CFLAGS)

client.o: client.c wrap.h
	gcc -c client.c $(CFLAGS)

wrap.o: wrap.c
	gcc -c wrap.c $(CFLAGS)

clean:
	@echo "cleanning project"
	-rm server client *.o
	@echo "clean completed"

.PHONY: clean
