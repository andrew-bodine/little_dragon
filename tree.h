/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: syntax tree
 */

#ifndef TREE_H
#define TREE_H

/* includes */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "sym_table.h"

/* enums */
typedef enum {
	num,
	op,
	id
} node_type;

/* structs */
typedef struct t_node {
	node_type type;
	union {
		int ival;	/* NUM */
		int oval;	/* OP */
		entry *id;	/* ID */
	} attr;
	struct t_node *left, *right;
} t_node;

/* prototypes */
t_node *new_node( node_type type, t_node *left, t_node *right );	/* constructor */
void destroy_node( t_node *to_delete );					/* destructor */
void print_tree( t_node *root, int spaces );

#endif /* tree.h */
