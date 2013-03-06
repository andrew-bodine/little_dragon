/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: syntax tree
 */

/* includes */
#include "tree.h"

/* definitions */
t_node *new_node( node_type type, t_node *left, t_node *right ) {

	/* allocate/assert memory */
	t_node *ptr = ( t_node * )malloc( sizeof( t_node ) );
	assert( ptr != NULL );

	/* set info */
	ptr->type = type;
	ptr->left = left;
	ptr->right = right;

	return ptr;
}
void destroy_node( t_node *to_delete ) {
	if( to_delete->left != NULL )
		destroy_node( to_delete->left );
	if( to_delete->right != NULL )
		destroy_node( to_delete->right );
	free( to_delete );
}
void print_tree( t_node *root, int spaces ) {
	int i;

	if( root == NULL ) return;

	for( i = 0; i < spaces; i++ )
		fprintf( stderr, " " );
	
	switch( root->type ) {
	case op:
		fprintf( stderr, "[OP:%c]", root->attr.oval );
		break;
	case num:
		fprintf( stderr, "[NUM:%d]", root->attr.ival );
		break;
	case id:
		fprintf( stderr, "[ID:%s]", root->attr.id );
		break;
	default:
		fprintf( stderr, "[UNKNOWN]" );
		break;
	}
	fprintf( stderr, "\n" );

	print_tree( root->left, spaces + 4 );
	print_tree( root->right, spaces + 4 );
}
