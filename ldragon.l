/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: lex
 */

%{

#ifndef LDRAGON_L
#define LDRAGON_L

 /* includes */
#include <stdlib.h>
#include "y.tab.h"

#include <stdio.h> // TO DELETE

 /* prototypes */
void yyerror( char * );

#endif /* ldragon.l */

%}

 /* regular definitions */
whitespace	[ \t\n]+
digit		[0-9]
number		{digit}+(\.{digit}+)?(e[+-]?{digit}+)?

%%

{whitespace}	{ /* no action and no return */ }

{number}	{
			//fprintf( stderr, "[ NUM: %d ]", atoi( yytext ) );
			yylval.ival = atoi( yytext );
			return NUM;
		}

"+"		{ /*fprintf( stderr, "[ OP: %d ]", ADD );*/ return ADD; }
"-"		{ /*fprintf( stderr, "[ OP: %d ]", SUB );*/ return SUB; }
"*"		{ /*fprintf( stderr, "[ OP: %d ]", MUL );*/ return MUL; }
"("		{ /*fprintf( stderr, yytext );*/ return OP; }
")"		{ /*fprintf( stderr, yytext );*/ return CP; }

.		{ yyerror( "unrecognized input" ); }

%%

int yywrap( ) {
	return 1;
}
