#include "gencode.h"

int main( ) {

	r_node *popped1, *popped2;
	r_node *rstack = init_rstack( );
	fprintf( stderr, "RSTACK:\n" );
	print_rstack( rstack );

	fprintf( stderr, "POPPING..\n" );
	popped1 = pop( &rstack );
	fprintf( stderr, "RSTACK:\n" );
	print_rstack( rstack );

	fprintf( stderr, "POPPING..\n" );
	popped2 = pop( &rstack );
	fprintf( stderr, "RSTACK:\n" );
	print_rstack( rstack );

	fprintf( stderr, "PUSHING..\n" );
	rstack = push( rstack, popped1 );
	fprintf( stderr, "RSTACK:\n" );
	print_rstack( rstack );

	fprintf( stderr, "PUSHING..\n" );
	rstack = push( rstack, popped2 );
	fprintf( stderr, "RSTACK:\n" );
	print_rstack( rstack );

	destroy_rstack( rstack );

	return 0;
}
