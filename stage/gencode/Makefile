OBJS = test.o gencode.o
CC = gcc
CFLAGS = -c -Wall
LFLAGS = -Wall

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o stage

test.o: gencode.h test.c
	$(CC) $(CFLAGS) test.c

gencode.o: gencode.c gencode.h
	$(CC) $(CFLAGS) gencode.c

clean:
	rm -rf *.o stage
