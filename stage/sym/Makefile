# Andrew C. Bodine
# Compilers - Little Dragon
# module: make

OBJS = stage.o sym_table.o
CC = gcc
CFLAGS = -c -Wall
LFLAGS = -Wall

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o stage

stage.o: stage.c sym_table.h
	$(CC) $(CFLAGS) stage.c

sym_table.o: sym_table.c sym_table.h
	$(CC) $(CFLAGS) sym_table.c

clean:
	rm -rf *.o stage
