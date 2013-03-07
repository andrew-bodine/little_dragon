#include "sym_table.h"

int main( ) {

	scope *s = NULL;
	entry *e1, *e2, *e3, *to_find;

	s = push_scope( s );
	e1 = new_entry( s, "foo" );
	e2 = new_entry( s, "bar" );
	s = push_scope( s );
	e3 = new_entry( s, "moo" );

	if( ( to_find = find_entry( s, "moo" ) ) != NULL )
		fprintf( stderr, "found %s in symbol table\n", to_find->name );
	else
		fprintf( stderr, "didn't find desired entry in symbol table\n" );

	return 0;
}
