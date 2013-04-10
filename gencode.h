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
#include "tree.h"

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
r_node *swap( r_node *rstack );				/* swaps top two register nodes on stack */
void print_rstack( r_node *rstack );
void label( t_node *root, int type );			/* type: 0 = root, 1 = left, 2 = right */
int moao( t_node *left, t_node *right ); 		/* max or add one: for labeling a node based on its children's ranks */
void gencode( t_node *root, r_node *rstack, int type );	/* type: 0 = left, 1 = right */

#endif /* gencode.h */
