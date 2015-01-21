#include "common.h"

static SNode* LinkInsert(SNode *head,SNode *newNode);
static void LinkPrint(SNode *head);
static SNode* LinkDelete(SNode *head,ElemType e);
static SNode* LinkDestroy(SNode *head);


/*

void DataStructure()
{
	int i;
	//队列
	//SQueue queue;
	//QueueInit(&queue);
	//_beginthread(WriteToQueue,0,&queue);
	//WriteToQueue(&queue);
	//free(queue.addr);

	//链表
	SNode* head = (SNode*)malloc(sizeof(SNode));
	head->next = head;
	head->pre = head;
	for(i=0; i<5; i++)
	{
		SNode* node = (SNode*)malloc(sizeof(SNode));
		node->element = i+1;
		LinkInsert(head,node);
	}
	for(i=3; i<7;i++)
	{
		LinkDelete(head,i);
		LinkPrint(head);
	}

	LinkPrint(head);
	head = LinkDestroy(head);
	LinkPrint(head);

}

*/
SNode* LinkInsert(SNode *head,SNode *node)
{
	//SNode* node;
	head->next->pre = node;
	node->next = head->next;
	node->pre = head;
	head->next = node;

	return head;
}


void LinkPrint(SNode *head)
{
	SNode *nil = head;
	head = head->next;
	while(head != nil)
	{
		printf("%d ",head->element);
		head = head->next;
	}
	printf("-\n");
}


SNode* LinkDelete(SNode *head,ElemType e)
{
	SNode *ptr = head->next;
	while(ptr != head)
	{
		if(ptr->element != e)
		{
			ptr = ptr->next;
		}
		else
		{
			ptr->pre->next = ptr->next;
			ptr->next->pre = ptr->pre;
			free(ptr);
			break;
		}

	}
	return head;
}


SNode* LinkDestroy(SNode *head)
{
	SNode *ptr,*nil = head;
	head = head->next;
	while(head != nil)
	{
		ptr = head;
		//printf("%d ",head->element);
		head = head->next;
		free(head->pre);
	}
	//printf("-\n");
	head->next = head;
	head->pre = head;
	return head;
}

/*

void DataStructure()
{
	int i;
	//队列
	//SQueue queue;
	//QueueInit(&queue);
	//_beginthread(WriteToQueue,0,&queue);
	//WriteToQueue(&queue);
	//free(queue.addr);

	//链表
	//SNode* head = (SNode*)malloc(sizeof(SNode));
	SNode* head =NULL;
	//head->next = head;
	//head->pre = head;
	for(i=0; i<5; i++)
	{
		//SNode* node = (SNode*)malloc(sizeof(SNode));
		SNode node;
		node.element = i+1;
		head = LinkInsert(head,&node);
	}
	for(i=3; i<7;i++)
	{
		head = LinkDelete(head,i);
		LinkPrint(head);
	}

	LinkPrint(head);
	head = LinkDestroy(head);
	LinkPrint(head);

}



static SNode* LinkInsert(SNode *head,SNode *newNode)
{
	SNode* node,*ptr = head,*pt;
	assert(NULL != (node = (SNode*)malloc(sizeof(SNode))));
	node->element = newNode->element;
	if(head == NULL)
	{
		head = node;
		node->next = NULL;
		node->pre = NULL;
	}
	else
	{
		while(ptr != NULL)
		{
			if(ptr->element < node->element)
			{
				pt = ptr;
				ptr = ptr->next;
			}
			else
			{
				//ptrb->next = node;
				ptr->pre->next=node;
				node->pre = ptr->pre;
				node->next = ptr;
				ptr->pre = node;
			}
		}
		if(ptr == NULL)
		{
			pt->next = node;
			node->pre = pt;
			node->next = NULL;
		}
	}
	return head;
}


static void LinkPrint(SNode *head)
{
	while(head!=NULL)
	{
		printf("%d ",head->element);
		head = head->next;
	}
	printf("-\n");
}


static SNode* LinkDelete(SNode *head,ElemType e)
{
	SNode *ptr = head;
	while(ptr != NULL)
	{
		if(ptr->element != e)
		{
			ptr = ptr->next;
		}
		else if(ptr == head)
		{
			head = ptr->next;
			free(ptr);
			break;
		}
		else if(ptr->next == NULL)
		{
			//ptrb->next = NULL;
			ptr->pre->next = NULL;
			free(ptr);
			break;
		}
		else
		{
			ptr->pre->next = ptr->next;
			ptr->next->pre = ptr->pre;
			free(ptr);
			break;
		}
	}
	return head;
}


static SNode* LinkDestroy(SNode *head)
{
	SNode *ptr;
	while(head!=NULL)
	{
		ptr = head;
		//printf("%d ",head->element);
		head = head->next;
		free(ptr);
	}
	//printf("-\n");
	return head;
}



*/
