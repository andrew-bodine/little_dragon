/* Andrew C. Bodine
 * Compilers - Little Dragon 
 * module: symbol table
 */

#ifndef SYM_TABLE_H
#define SYM_TABLE_H

/* includes */
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>

/* constants */
#define TABLE_SIZE 211

/* structs */
typedef struct entry {
	char *name;
	int *value;
	struct entry *next;
} entry; // id entry
typedef struct scope {
	entry *sym_t[ TABLE_SIZE ];
	struct scope *parent;
} scope; // scope entry

/* prototypes */
entry *new_entry( scope *stack, char *name );
void destroy_entry( entry *to_delete );
scope *push_scope( scope *stack );
scope *pop_scope( scope *stack );
int hashpjw( const void *key, int tablesize );
void print_symstack( scope *stack );

#endif /* sym_table.h */
