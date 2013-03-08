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
#include "sym_table.h"

/* pointers */
t_node *tptr, *tptr2;
scope *sptr;
entry *eptr;

/* prototypes */
int yylex( void );
void yyerror( char *s );

#endif /* ldragon.y */

%}

/* yylval union */
%union {
	int ival;	/* integer */
	t_node *tval;	/* syntax tree node */
	char *sval;	/* id */
};

/* tokens */
%token <ival> NUM
%token <sval> ID

/* precedence */
%left '+' '-'
%right '*'

/* types */
%type <tval> stmts stmt expr

/* start */
%start prgm

%%

prgm	: '\n' prgm		{	/* ignore before { */; }
     	| '{' 			{ 	sptr = push_scope( sptr ); }
	  stmts 
	  '}' post		{ 	
					print_symstack( sptr );
					sptr = pop_scope( sptr );
			}
     	;

post	: '\n' post		{	/* ignore after */; }
	| /* empty */		{;}
	;

stmts	: stmt stmts		{	$$ = $1; }	
      	| '\n' stmts		{;}
	| /* empty */		{;}
      	;

stmt	: ID '=' expr		{ 
     					eptr = new_entry( sptr, $1 );
					tptr = new_node( id, NULL, NULL );
					tptr->attr.id = eptr;
					tptr2 = new_node( op, tptr, $3 );
					tptr2->attr.oval = '=';
					$$ = tptr2;
					print_tree( $$, 0 );
					// set *( eptr->value ) = eval_stmt( $$ );
				}
	| expr			{	print_tree( $1, 0 ); }
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
	| '(' expr ')'		{	$$ = $2; }

	/* IDENT */

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
