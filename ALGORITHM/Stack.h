#ifndef STACK_H
#define STACK_H
#include "common.h"

#ifdef TREE
	#define SElemType Tree
#else 
	#define SElemType ElemType
#endif


typedef struct _SqSTACK{
	SElemType *base;
	SElemType *top;
	int stackSize;
}SqSTACK;

extern status StackInit(SqSTACK* stack);
extern status Push(SqSTACK* stack,SElemType e);
extern SElemType Pop(SqSTACK* stack);
extern status StackDestroy(SqSTACK* stack);
SElemType StackGetTop(SqSTACK* stack);
status StackIsEmpty(SqSTACK* stack);
#endif