/* test.c */

#include "tree.h"

int main( ) {

	t_node *n1, *n2, *n3;

	n1 = new_node( num, NULL, NULL );
	n1->attr.ival = 1;
	n2 = new_node( num, NULL, NULL );
	n2->attr.ival = 2;
	n3 = new_node( op, n1, n2 );
	n3->attr.oval = '+';

	print_tree( n3, 0 );

	destroy_node( n3 );

	print_tree( n3, 0 );

	fprintf( stderr, "n2: %d\n", n3->left->attr.ival );

	return 0;
}
