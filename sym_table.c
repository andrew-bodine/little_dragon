/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: symbol table
 */

/* includes */
#include "sym_table.h"

/* definitions */
entry *new_entry( scope *stack, char *name ) {
	entry *ptr;
	int index;

	/* must have a symbol table */
	assert( stack != NULL );

	/* allocate/assert memory */
	ptr = ( entry * )malloc( sizeof( entry ) );
	assert( ptr != NULL );

	/* set info */
	ptr->name = strdup( name );
	ptr->value = 0;
	ptr->next = NULL;

	/* insert new entry */
	index = hashpjw( name, TABLE_SIZE );
	if( stack->sym_t[ index ] == NULL )
		stack->sym_t[ index ] = ptr;
	else {
		ptr->next = stack->sym_t[ index ];
		stack->sym_t[ index ] = ptr;
	}

	return ptr;
}
void destroy_entry( entry *to_delete ) {
	if( to_delete == NULL )
		return;
	else {
		destroy_entry( to_delete->next );
		free( to_delete->name );
		free( to_delete );
	}
}
entry *find_entry( scope *stack, char *name ) {
	scope *s = stack;
	entry *ptr = NULL;
	int i;

	while( s != NULL ) {
		for( i = 0; i < TABLE_SIZE; i++ ) {
			if( s->sym_t[ i ] != NULL ) {
				ptr = s->sym_t[ i ];
				while( ptr != NULL ) {
					if( strncmp( name, ptr->name, strlen( name ) ) == 0 )
						return ptr;
					ptr = ptr->next;
				}
			}
		}
		s = s->parent;
	}
	return NULL;
}
scope *push_scope( scope *stack ) {
	scope *ptr;

	/* allocate/assert memory */
	ptr = ( scope * )malloc( sizeof( scope ) );
	assert( ptr != NULL );

	/* set info */
	if( stack != NULL )
		ptr->parent = stack;
	else
		ptr->parent = NULL;

	return ptr;
}
scope *pop_scope( scope *stack ) {
	scope *ptr;
	int i;

	if( stack == NULL )
		return NULL;
	else {
		ptr = stack->parent;

		for( i = 0; i < TABLE_SIZE; i++ ) {
			if( stack->sym_t[ i ] != NULL )
				destroy_entry( stack->sym_t[ i ] );
		}

		free( stack );
		return ptr;
	}
}
int hashpjw( const void *key, int tablesize ) {
	const char *ptr = key;
	int val = 0;

	while( *ptr != '\0' ) {
		int tmp;
		val = ( ( val << 4 ) + ( *ptr ) );
		if( ( tmp = ( val & 0xf0000000 ) ) ) {
			val = val ^ ( tmp >> 24 );
			val = val ^ tmp;
		}
		ptr++;
	}
	return val % tablesize;
}
void print_symstack( scope *stack ) {
	scope *s = stack;
	entry *e;
	int i;

	while( s != NULL ) {
		for( i = 0; i < TABLE_SIZE; i++ ) {
			if( ( e = s->sym_t[ i ] ) != NULL ) {
				while( e != NULL ) {
					fprintf( stderr, "[%s:%d]", e->name, e->value );
					e = e->next;
				}
				fprintf( stderr, "\n" );
			}
		}
		fprintf( stderr, "---------------------\n" );
		s = s->parent;
	}
}
