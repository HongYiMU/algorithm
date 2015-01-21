#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

#ifdef TREE
	#define QElemType Tree
#else
	#define QElemType ElemType
#endif

typedef struct _SQueue{
	QElemType *addr; 
	int head;
	int tail;
	int size;
}SQueue;


status QueueInit(SQueue* queue);
status QueueDestroy(SQueue* queue);
status QueueWrite(SQueue* queue,QElemType e);
status QueueRead(SQueue* queue,QElemType* e);
BOOL QueueIsEmpty(SQueue* queue);
void QueuePrint(SQueue* queue);

#endif

