/* test.c */

#include <stdio.h>
#include "hashpjw.h"

int main( ) {

	int hval;

	hval = hashpjw( "foobars", 26 );
	fprintf( stderr, "HASH :: %d\n", hval );

	return 0;
}
