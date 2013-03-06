#include <stdio.h>
#include "sym_table.h"

int main( ) {

	entry *e1, *e2, *e3;
	scope *stack = NULL;

	stack = push_scope( stack );
	e1 = new_entry( stack, "foobar", 5 );
	e2 = new_entry( stack, "raboof", 9 );
	stack = push_scope( stack );
	e3 = new_entry( stack, "monkey", 3 );

	print_symstack( stack );

	return 0;
}
