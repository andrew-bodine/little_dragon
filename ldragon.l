/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: lex
 */

%{

#ifndef LDRAGON_L
#define LDRAGON_L

 /* includes */
#include <stdlib.h>
#include "tree.h"
#include "y.tab.h"

 /* prototypes */
void yyerror( char * );

#endif /* ldragon.l */

%}

%option nounput noinput

 /* regular definitions */
whitespace	[ \t]+
digit		[0-9]
number		{digit}+(\.{digit}+)?(e[+-]?{digit}+)?
letter		[a-zA-Z_]+
id		{letter}({letter}|{digit})*
token		[-+*()\n={}]

%%

{whitespace}	{ /* no action and no return */ }

"print"		{ return PRINT; }

{number}	{
			yylval.ival = atoi( yytext );
			return NUM;
		}

{id}		{ 
			yylval.sval = strdup( yytext );
			return ID;
		}

{token}		{ return yytext[ 0 ]; }

.		{ yyerror( "unrecognized input" ); }

%%

int yywrap( ) {
	return 1;
}
