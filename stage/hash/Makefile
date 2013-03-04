OBJS = hashpjw.o test.o
CC = gcc
LEX = lex
YACC = yacc
YFLAGS = -d -v
CFLAGS = -c -Wall
LFLAGS = -Wall
#LFLAGS = -Wall -lfl


all: $(OBJS)
	$(CC) -o stage $(OBJS) $(LFLAGS) 

test.o: test.c hashpjw.h
	$(CC) $(CFLAGS) test.c

hashpjw.o: hashpjw.c hashpjw.h
	$(CC) $(CFLAGS) hashpjw.c

clean:
	rm -rf *.o lex.yy.c *.tab.* stage *.output
