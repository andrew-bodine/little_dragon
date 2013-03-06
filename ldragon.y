/* Andrew C. Bodine 
 * Compilers - Little Dragon
 * module: yacc
 */

%{

#ifndef LDRAGON_Y
#define LDRAGON_Y

/* includes */
#include <stdio.h>
#include "tree.h"

/* pointers */
t_node *tptr;

/* prototypes */
int yylex( void );
void yyerror( char *s );

#endif /* ldragon.y */

%}

/* yylval union */
%union {
	int ival;	/* integer */
	t_node *tval;	/* syntax tree node */
};

/* tokens */
%token <ival> NUM

/* precedence */
%left '+' '-'
%right '*'

/* types */
%type <tval> prgm prgm_ expr

%%

prgm	: expr '\n' prgm_	{ print_tree( $1, 0 ); }
     	;

prgm_	: expr '\n' prgm_	{ print_tree( $1, 0 );}
      	| '\n'			{;}
	| /* empty */		{;}
      	;

expr	: expr '+' expr		{
     					tptr = new_node( op, $1, $3 );
					tptr->attr.oval = '+';
					$$ = tptr;
				}
     	| expr '-' expr		{
					tptr = new_node( op, $1, $3 );
					tptr->attr.oval = '-';
					$$ = tptr;
				}
	| expr '*' expr		{
					tptr = new_node( op, $1, $3 );
					tptr->attr.oval = '*';
					$$ = tptr;
				}
	| NUM			{
					tptr = new_node( num, NULL, NULL );
					tptr->attr.ival = $1;
					$$ = tptr;
				}
	;

%%

void yyerror( char *s ) {
	fprintf( stderr, "%s\n", s );
}

int main( void ) {
	yyparse( );
	return 0;
}
