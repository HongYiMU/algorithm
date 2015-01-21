//#include "common.h"
#include "Queue.h"
status QueueInit(SQueue* queue);
status QueueDestroy(SQueue* queue);
status QueueWrite(SQueue* queue,QElemType e);
status QueueRead(SQueue* queue,QElemType* e);
void QueuePrint(SQueue* queue);


void QueuePrint(SQueue* queue)
{
	int i;

	for(i=0; i<MAX_INIT_SIZE; i++)
	{
		printf("%c ",queue->addr[i]);
	}
	printf("=========\n");
}
status QueueInit(SQueue* queue)
{
	assert( NULL != (queue->addr = (QElemType*)malloc(sizeof(QElemType)*MAX_INIT_SIZE)));
	queue->head = -1;
	queue->tail = 0;
	queue->size = MAX_INIT_SIZE;
	memset(queue->addr,0,queue->size);

	return 0;
}

status QueueDestroy(SQueue* queue)
{
	if(queue != NULL)
	{
		free(queue->addr);
	}
	return 1;
}
/************************************************************************/
//tail keep empty
/************************************************************************/

status QueueWrite(SQueue* queue,QElemType e)
{		
	assert(queue != NULL);
	if(queue->tail == queue->head)
	{
		printf("over flow\n");
		return -1;
	}
	else
	{
		queue->addr[queue->tail] = e;
	}

	if(queue->tail == queue->size-1)
	{
		queue->tail = 0;
	}
	else
	{
		queue->tail += 1;
	}
	if(queue->head == -1)
	{
		queue->head = 0;
	}
	return 0;
}



status QueueRead(SQueue* queue,QElemType* e)
{
	if(queue->head < 0)
	{
		printf("Queue is empty\n");
		//*e = '\r';
		return -1;
	}
	*e = queue->addr[queue->head];
	if(queue->head == queue->size-1)
	{
		queue->head = 0;
	}
	else
	{
		queue->head += 1;
	}
	if(queue->head == queue->tail)
	{
		queue->head = -1;
		queue->tail = 0;
	}
	return 0;
}

BOOL QueueIsEmpty(SQueue* queue)
{
	int ret = 0;
	if(queue->head < 0)
	{
		return 1;
	}
	return ret;
}
#ifndef TREE
void WriteToQueue(SQueue* queue)
{
	QElemType get,read;
	printf("anykey to start\n");
	while((get = fgetc(stdin)) != 'q')
	{
		printf("\nr/w to switch\nwrite:\n");
		while((get = fgetc(stdin)) != 'r')
		{
			printf(">>%c ",get);
			QueueWrite(queue,get);
		}
		QueuePrint(queue);

		printf("read:\n");
		while((get = fgetc(stdin)) != 'w')
		{
			read = '=';
			QueueRead(queue,&read);
			printf("%c ",read);
		}

	}
}
#endif