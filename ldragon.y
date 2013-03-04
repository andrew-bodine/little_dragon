/* Andrew C. Bodine 
 * Compilers - Little Dragon
 * module: yacc
 */

%{

#ifndef LDRAGON_Y
#define LDRAGON_Y

/* includes */
#include <stdio.h>

/* prototypes */
int yylex( void );
void yyerror( char *s );

#endif /* ldragon.y */

%}

/* yylval union */
%union {
	int ival;	/* integer value */
};

/* tokens */
%token OP		/* open parentheses */
%token CP		/* close parentheses */
%token ADD		/* add */
%token SUB		/* subtract*/
%token MUL		/* multiply */
%token <ival> NUM	/* number constant */

/* precedence */
%left '+' '-'
%right '*'

%%

expr	: term expr_		{;}
	;

expr_	: ADD term expr_	{;}
	| SUB term expr_	{;}
	| /* empty */
	;

term	: factor term_		{;}
     	;

term_	: MUL term		{;}
      	| /* empty */
	;

factor	: OP expr CP		{;}
       	| NUM
	;

%%

void yyerror( char *s ) {
	fprintf( stderr, "%s\n", s );
}

int main( void ) {
	yyparse( );
	return 0;
}
