/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module - semantic evaluation
 */

/* includes */
#include "semantics.h"

/* definitions */
int eval_tree( t_node *ptr ) {
	assert( ptr != NULL );

	switch( ptr->type ) {
	case op:
		switch( ptr->attr.oval ) {
		case '+':
			return eval_tree( ptr->left ) + eval_tree( ptr->right );
		case '*':
			return eval_tree( ptr->left ) * eval_tree( ptr->right );
		case '-':
			return eval_tree( ptr->left ) - eval_tree( ptr->right );
		default:
			fprintf( stderr, "Unknown operator type: %d\n", ptr->attr.oval );
			exit( 1 );
		}
	case num:
		return ptr->attr.ival;
	case id:
		return ptr->attr.id->value;
	default:
		fprintf( stderr, "Unknown node type: %d\n", ptr->type );
		exit( 1 );
	}
}
int eval_stmt( t_node *ptr ) {
	int value;
	t_node *id;

	assert( ptr != NULL );

	/* maybe not switching on oval? but type instead?
	 * come back to this!!! */
	switch( ptr->attr.oval ) {
	case '=':
		id = ptr->left;
		assert( id != NULL );
		assert( ptr->right != NULL );
		value = eval_tree( ptr->right );
		assert( id->attr.id != NULL );
		id->attr.id->value = value;

		/* gencode */
		r_node *rstack = init_rstack( );
		label( ptr->right );
		destroy_rstack( rstack );

		return value;
	case 'p':
		value = eval_tree( ptr->left );
		return value;
	default:
		fprintf( stderr, "Unknown operator type: %d\n", ptr->attr.oval );
		exit( 1 );
	}
}
