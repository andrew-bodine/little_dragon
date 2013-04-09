#ifndef SEMANTICS_H
#define SEMANTICS_H

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "gencode.h"

/* prototypes */
int eval_tree( t_node *ptr );
int eval_stmt( t_node *ptr ); 

#endif /* semantics.h */
