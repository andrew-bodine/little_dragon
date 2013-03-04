# Andrew C. Bodine
# Compilers - Little Dragon
# module: make

OBJS = lex.yy.o y.tab.o
CC = gcc
LEX = lex
YACC = yacc
YFLAGS = -v -d
CFLAGS = -c -Wall
LFLAGS = -Wall -lfl

all: $(OBJS)
	$(CC) -o ldragon $(OBJS) $(LFLAGS) 

y.tab.o: y.tab.c y.tab.h
	$(CC) $(CFLAGS) y.tab.c

lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CFLAGS) lex.yy.c

y.tab.c y.tab.h: ldragon.y
	$(YACC) $(YFLAGS) ldragon.y

lex.yy.c: ldragon.l
	$(LEX) ldragon.l

clean:
	rm -rf *.o lex.yy.c *.tab.*  ldragon *.output
