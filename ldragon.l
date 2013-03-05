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

 /* regular definitions */
whitespace	[ \t]+
digit		[0-9]
number		{digit}+(\.{digit}+)?(e[+-]?{digit}+)?
token		[-+*()\n]

%%

{whitespace}	{ /* no action and no return */ }

{number}	{
			yylval.ival = atoi( yytext );
			return NUM;
		}

{token}		{ return yytext[ 0 ]; }

.		{ yyerror( "unrecognized input" ); }

%%

int yywrap( ) {
	return 1;
}
