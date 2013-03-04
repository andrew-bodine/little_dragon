/* Andrew C. Bodine
 * Compilers - Little Dragon 
 * module: symbol table
 */

/* NOTE: the symbol table is implented with a few arrays and linked lists.
 * 	-> master symbol( hash ) table to manage function scopes
 * 	-> individual symbol( hash ) table for each function scope
 * 	-> procedural blocks { if, else, while, etc } included in each symbol tables ( master and children )*/

#ifndef SYM_TABLE_H
#define SYM_TABLE_H

/* includes */

/* structs */
typedef struct {
	/* hastable? */
	snode *prev, *next;
} snode;

/* prototypes */

#endif /* sym_table.h */
