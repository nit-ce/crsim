CC = cc
CFLAGS = -Wall -O2
LDFLAGS =

all: main

%.o: %.c
	$(CC) -c $(CFLAGS) $<
main: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o main
