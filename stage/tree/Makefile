OBJS = tree.o test.o
CC = gcc
CFLAGS = -c -Wall
LFLAGS = -Wall


all: $(OBJS)
	$(CC) -o stage $(OBJS) $(LFLAGS) 

test.o: test.c tree.h
	$(CC) $(CFLAGS) test.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) tree.c

clean:
	rm -rf *.o stage
