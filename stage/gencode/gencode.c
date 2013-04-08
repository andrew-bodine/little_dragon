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
