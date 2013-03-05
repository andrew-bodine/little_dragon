/* Andrew C. Bodine
 * Compilers - Little Dragon
 * module: syntax tree
 */

#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* enums */
typedef enum {
	number,
	operation
} node_type;

/* structs */
typedef struct num_node {
	int value;
} num_node; /* number */

typedef struct op_node {
	int value;
	struct tree_node *loper, *roper;
} op_node; /* operation */

typedef struct tree_node {
	node_type type;
	union {
		num_node num;
		op_node op;
	};
} tree_node; /* abstract tree node */

/* prototypes */
//tree_node *n_node( int value );
//tree_node *o_node( int op, tree_node *loper, tree_node *roper );
//void print_tree( tree_node *root, int spaces );
//int max_depth( tree_node *root );

#endif /* syntax_tree.h */
