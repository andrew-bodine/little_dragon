/* test.c */

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

int main( ) {

	tree_node *loper, *roper, *op;

	loper = n_node( 7 );
	roper = n_node( 13 );
	op = o_node( '+', loper, roper );

	//fprintf( stderr, "%d %c %d\n", op->op.loper->num.value, op->op.value, op->op.roper->num.value);
	print_tree( op );

	free( loper );

	return 0;
}
