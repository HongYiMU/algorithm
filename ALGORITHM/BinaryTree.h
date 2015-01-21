#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "common.h"

typedef struct BinSrchNode{
	struct BinSrchNode* left,*right,*p;
	int key;
}BSNODE,*BSTREE;


#endif

