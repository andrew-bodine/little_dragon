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
void print_tree( tree_node *root, int spaces ) {
	int i;
	
	if( root == NULL ) return;

	for( i = 0; i < spaces; i++ )
		fprintf( stderr, " " );

	switch( root->type ) {
	case operation:
		fprintf( stderr, "[OP:%c]", root->op.value );
		break;
	case number:
		fprintf( stderr, "[NUM:%d]", root->num.value );
		break;
	default:
		fprintf( stderr, "[UNKNOWN]" );
		break;
	}
	fprintf( stderr, "\n" );

	if( root->type == operation ) {
		print_tree( root->op.loper, spaces + 4 );
		print_tree( root->op.roper, spaces + 4 );
	}
}
int max_depth( tree_node *root ) {

	if( root == NULL )
		return 0;
	else if( root->type == number )
		return 1;
	else {
		int lsum = max_depth( root->op.loper );
		int rsum = max_depth( root->op.roper );
		return 1 + ( ( lsum > rsum ) ? lsum : rsum );
	}
}
