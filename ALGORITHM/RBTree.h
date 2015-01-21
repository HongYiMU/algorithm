#ifndef RB_TREE_H
#define RB_TREE_H
#include "common.h"

//302419016
typedef enum{RED,BLACK}COLOR;

typedef struct RB_NODE{
	struct RB_NODE *left,*right,*p;
	int key;
	COLOR color;
}RB_NODE,*RB_TREE;

void RBTree();

#endif
