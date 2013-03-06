# Andrew C. Bodine
# Compilers - Little Dragon
# module: make

OBJS = sym_table.o tree.o lex.yy.o y.tab.o
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

y.tab.c y.tab.h: ldragon.y tree.h sym_table.h
	$(YACC) $(YFLAGS) ldragon.y

lex.yy.c: ldragon.l tree.h sym_table.h
	$(LEX) ldragon.l

tree.o: tree.c tree.h sym_table.h
	$(CC) $(CFLAGS) tree.c

sym_table.o: sym_table.c sym_table.h
	$(CC) $(CFLAGS) sym_table.c

clean:
	rm -rf *.o lex.yy.c *.tab.*  ldragon *.output
