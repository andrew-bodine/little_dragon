/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: code generation
 */

/* includes */
#include "gencode.h"

/* definitions */
r_node *new_rnode( int number ) {
	r_node *ptr;

	/* allocate/assert memory */
	ptr = ( r_node * )malloc( sizeof( r_node ) );
	assert( ptr != NULL );

	/* set info */
	ptr->number = number;
	ptr->next = NULL;

	return ptr;
}
void destroy_rnode( r_node *to_delete ) {
	if( to_delete == NULL )
		return;
	free( to_delete );
}
r_node *init_rstack( ) {
	r_node *ptr;

	ptr = new_rnode( 0 );
	return ptr;
}
void destroy_rstack( r_node *rstack ) {
	if( rstack == NULL )
		return;
	destroy_rstack( rstack->next );
	destroy_rnode( rstack );
}
r_node *push( r_node *rstack, r_node *new_top ) {
	assert( rstack != NULL && new_top != NULL );

	new_top->next = rstack;
	return new_top;
}
r_node *pop( r_node **rstack ) {
	
	/* pop register */
	r_node *ptr = *rstack;
	*rstack = (*rstack)->next;

	/* dynamically add registers when stack is emtpy */
	if( *rstack == NULL )
		*rstack = new_rnode( ptr->number + 1 );

	return ptr;
}
void print_rstack( r_node *rstack ) {
	if( rstack == NULL )
		fprintf( stderr, "---------------------\n" );
	else {
		fprintf( stderr, "[ R%d ]\n", rstack->number );
		print_rstack( rstack->next );
	}
}
void label( t_node *root, int type ) {
	if( type == 0 ) {
		
		/* if only root node to label .: assign rank 0 to skip gencode( ) */
		if( root->left == NULL && root->right == NULL )
			root->gcl = 0;
		else {
			label( root->left, 1 );
			label( root->right, 2 );
			root->gcl = moao( root->left, root->right );
		}
	}
	else if( type == 1 ) {

		/* left most child .: leaf */
		if( root->left == NULL && root->right == NULL )
			root->gcl = 1;
		else {
			label( root->left, 1 );
			label( root->right, 2 );
			root->gcl = moao( root->left, root->right );
		}
	}
	else {
		
		/* right most child .: leaf */
		if( root->left == NULL && root->right == NULL )
			root->gcl = 0;
		else {
			label( root->left, 1 );
			label( root->right, 2 );
			root->gcl = moao( root->left, root->right );
		}
	}
}
int moao( t_node *left, t_node *right ) {

	/* if gcl's are equal .: return gcl + 1 */
	if( left->gcl == right->gcl )
		return left->gcl + 1;

	/* else .: return max */
	else if( left->gcl > right->gcl )
		return left->gcl;
	else
		return right->gcl;
}
void gencode( t_node *root, r_node *rstack ) {
	
	/* case 0 */
	if( root->left == NULL && root->right == NULL ) {
		if( root->type == num )
			fprintf( stderr, "MOV %d, R%d\n", root->attr.ival, rstack->number );
		else if( root->type == id )
			fprintf( stderr, "MOV %s, R%d\n", root->attr.id->name, rstack->number );
	}
}
