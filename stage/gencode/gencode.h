/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: code generation
 */

#ifndef GENCODE_H
#define GENCODE_H

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* structs */
typedef struct r_node {
	int number;
	struct r_node *next;
} r_node; // register stack node

/* prototypes */
r_node *new_rnode( int number );
void destroy_rnode( r_node *to_delete );
r_node *init_rstack( );
void destroy_rstack( r_node *rstack );
r_node *push( r_node *rstack, r_node *new_top );
r_node *pop( r_node **rstack );
void print_rstack( r_node *rstack );

char *top( r_node *rstack );

#endif /* gencode.h */
