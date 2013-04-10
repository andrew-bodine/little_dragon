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
r_node *swap( r_node *rstack ) {
	r_node *new_top;

	assert( rstack != NULL );
	if( rstack->next == NULL ) {
		new_top = new_rnode( rstack->number + 1 );
		new_top->next = rstack;
	}
	else {
		new_top = rstack->next;
		rstack->next = new_top->next;
		new_top->next = rstack;
	}
	return new_top;
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
void gencode( t_node *root, r_node *rstack, int type ) {

	/** case 0 **/
	/* n is a left leaf representing operand name and n is the leftmost
	 * child of its parent */
	if( root->left == NULL && root->right == NULL && type == 0 ) {

		/* print 'MOV' || name || ',' || top( rstack ) */
		if( root->type == num )
			fprintf( stderr, "MOV %d, R%d\n", root->attr.ival, rstack->number );
		else if( root->type == id )
			fprintf( stderr, "MOV %s, R%d\n", root->attr.id->name, rstack->number );
	}

	/* n is an interior node with operator op, left child n1, and right child n2 */
	else if( root->left != NULL && root->right != NULL && root->type == op ) {

		/** case 1 **/
		/* if label( n2 ) = 0, let name be the operand represented by n2 */
		if( root->right->gcl == 0 ) {

			/* gencode( n1 ) */
			gencode( root->left, rstack, 0 );

			/* print op || name || ',' || top( rstack ) */
			switch( root->attr.oval ) {
			case '+':
				if( root->right->type == num )
					fprintf( stderr, "ADD %d, R%d\n", root->right->attr.ival, rstack->number );
				else if( root->right->type == id )
					fprintf( stderr, "ADD %s, R%d\n", root->right->attr.id->name, rstack->number );
				break;
			case '-':
				if( root->right->type == num )
					fprintf( stderr, "SUB %d, R%d\n", root->right->attr.ival, rstack->number );
				else if( root->right->type == id )
					fprintf( stderr, "SUB %s, R%d\n", root->right->attr.id->name, rstack->number );
				break;
			case '*':
				if( root->right->type == num )
					fprintf( stderr, "MUL %d, R%d\n", root->right->attr.ival, rstack->number );
				else if( root->right->type == id )
					fprintf( stderr, "MUL %s, R%d\n", root->right->attr.id->name, rstack->number );
				break;
			default:
				/* shouldn't get here */
				fprintf( stderr, "Unrecognized op value in gencode : case 1\n" );
			}
		}

		/** case 2 **/
		/* 1 <= label( n1 ) < label( n2 ) and label( n1 ) < total number of registers */
		else if( 1 <= root->left->gcl && root->left->gcl < root->right->gcl ) { //&& root->left->gcl < ( rstack->number + 1 ) ) {

			/* swap( rstack ) */
			rstack = swap( rstack );

			/* gencode( n2 ) */
			gencode( root->right, rstack, 1 );

			/* R := pop( rstack ), n2 was evaluated into register R */
			r_node *R = pop( &rstack );

			/* gencode( n1 ) */
			gencode( root->left, rstack, 0 );

			/* print op || R || ',' || top( rstack ) */
			switch( root->attr.oval ) {
			case '+':
				fprintf( stderr, "ADD R%d, R%d\n", R->number, rstack->number );
				break;
			case '-':
				fprintf( stderr, "SUB R%d, R%d\n", R->number, rstack->number );
				break;
			case '*':
				fprintf( stderr, "MUL R%d, R%d\n", R->number, rstack->number );
				break;
			default:
				/* shouldn't get here */
				fprintf( stderr, "Unrecognized op value in gencode : case 1\n" );
			}

			/* push( rstack, R ) */
			rstack = push( rstack, R );

			/* swap( rstack ) */
			rstack = swap( rstack );
		}

		/** case 3 **/
		/* 1 <= label( n2 ) <= label( n1 ) and label( n2 ) < total number of registers */
		else if( 1 <= root->right->gcl && root->right->gcl <= root->left->gcl ) { // && root->right->gcl < ( rstack->number + 1 ) ) {

			/* gencode( n1 ) */
			gencode( root->left, rstack, 0 );

			/* R := pop( rstack ), n1 was evaluated into register R */
			r_node *R = pop( &rstack );

			/* gencode( n2 ) */
			gencode( root->right, rstack, 1 );

			/* print op || top( rstack ) || ',' || R */
			switch( root->attr.oval ) {
			case '+':
				fprintf( stderr, "ADD R%d, R%d\n", rstack->number, R->number );
				break;
			case '-':
				fprintf( stderr, "SUB R%d, R%d\n", rstack->number, R->number );
				break;
			case '*':
				fprintf( stderr, "MUL R%d, R%d\n", rstack->number, R->number );
				break;
			default:
				/* shouldn't get here */
				fprintf( stderr, "Unrecognized op value in gencode : case 1\n" );
			}

			/* push( rstack, R ) */
			rstack = push( rstack, R );
		}

		/** case 4 **/
		/* both labels >= total number of registers */
		else {
			fprintf( stderr, "shouldn't get to gencode : case 4\n" );
		}
	}
}
