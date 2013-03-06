OBJS = sym_table.o test.o
CC = gcc
LEX = lex
YACC = yacc
YFLAGS = -d -v
CFLAGS = -c -Wall
LFLAGS = -Wall
#LFLAGS = -Wall -lfl


all: $(OBJS)
	$(CC) -o stage $(OBJS) $(LFLAGS) 

test.o: test.c sym_table.h
	$(CC) $(CFLAGS) test.c

sym_table.o: sym_table.c sym_table.h
	$(CC) $(CFLAGS) sym_table.c

clean:
	rm -rf *.o stage
