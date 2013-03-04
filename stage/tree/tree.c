/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: syntax tree
 */

/* includes */
#include "tree.h"

/* definitions */
tree_node *n_node( int value ) {
	tree_node *ptr;

	/* allocate/assert memory */
	ptr = ( tree_node * )malloc( sizeof( tree_node ) );
	assert( ptr != NULL );

	/* set info */
	ptr->type = number;
	ptr->num.value = value;

	return ptr;
}
tree_node *o_node( int op, tree_node *loper, tree_node *roper ) {
	tree_node *ptr;

	/* allocate/assert memory */
	ptr = ( tree_node * )malloc( sizeof( tree_node ) );
	assert( ptr != NULL );

	/* set info */
	ptr->type = operation;
	ptr->op.value = op;
	ptr->op.loper = loper;
	ptr->op.roper = roper;

	return ptr;
}
void print_tree( tree_node *root ) {
	tree_node *itr = root;

	if( itr->op.loper->type == number && itr->op.roper->type == number ) {
		fprintf( stderr, "    [ %c ]\n", itr->op.value );
		fprintf( stderr, "   /     \\\n" );
		fprintf( stderr, "[ %d ]  [ %d ]\n", itr->op.loper->num.value, itr->op.roper->num.value );
	}
}
