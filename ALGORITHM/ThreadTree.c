#include "common.h"
#include <process.h>
#include "Stack.h"
#include "Queue.h"


static BOOL BinTreeLookUp(Node* node, int target);
static Node* BinTreeInsert(Node* node, int data);
static Node* NewNode(int data);
static void BinTreePrint(Node* node);
static void CreatBiTree(Tree* T);
void PrintTree(Tree T);

void InThreading(Node* node);
void InOrderThreadHead(Tree* H,Tree P);
void InOrderTraverseThr(Tree T);

// void DataStructure()
// {
// 	Tree T=NULL;
// 	Tree header=NULL;
// 	CreatBiTree(&T);
// 
// 	BinTreePrint(T);
// 	printf("\n");
// 	//InOrderTraverse(T);
// 	//PreOrderTraverse(T);
// 	//PostOrderTraverse(T);
// 	//LevelOrderTraverse(T);
// 	//InOrderThreadHead(&header,T);
// 	//InOrderTraverseThr(header);
// 
// }
// 

static void CreatBiTree(Tree* T)
{
	ElemType ch[100] = "";
	int len;
	int i;
	fgets(ch,100,stdin);
	len = strlen(ch);
	for(i=0; i<len-1; i++)
	{
		*T = BinTreeInsert(*T, ch[i]);
	}
	printf("\n");


}
//http://zh.wikipedia.org/wiki/������

static BOOL BinTreeLookUp(Node* node, int target)
{
	if(node == NULL)
	{
		return FALSE;
	}
	else
	{
		if(node->data == target)
		{
			return TRUE;
		}
		else if (node->data < target)
		{
			return BinTreeLookUp(node->rChild,target);
		}
		else if(node->data > target)
		{
			return BinTreeLookUp(node->lChild,target);
		}
	}
	return FALSE;
}



static Node* BinTreeInsert(Node* node, int data)
{
	if(node == NULL)
	{
		return NewNode(data);
	}
	else
	{
		if(node->data >= data)
		{
			node->lChild = BinTreeInsert(node->lChild,data);
		}
		else
		{
			node->rChild = BinTreeInsert(node->rChild,data);
		}
		return node;
	}

}


static Node* NewNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	memset(newNode,0,sizeof(newNode));
	newNode->data = data;
	newNode->lChild = NULL;
	newNode->rChild = NULL;
#ifdef ThreadTree
	newNode->LTag = Link;
	newNode->RTag = Link;
#endif
	//newNode->parent = NULL;
	return newNode;
}


static void BinTreePrint(Node* node)
{
	if(node == NULL)
	{
		return ;
	}
	//printf("<%c>",node->data);//�������p,l,r
	BinTreePrint(node->lChild);
	printf("<%c>",node->data);//	�������l,p,r
	BinTreePrint(node->rChild);
	//printf("<%c>",node->data);//�������
}

//��������������

Node* preNode = NULL;//ȫ�ֱ�����ָ����ʹ�����һ����㡣
void InThreading(Node* node)
{
	if(node == NULL)
	{
		return ;
	}
	InThreading(node->lChild);
	if(!node->lChild)	//���û���������ó�������
	{
		node->LTag = Thread;	//�������ó�����
		node->lChild = preNode;	//ǰ������һ�����
	}
	if(!preNode->rChild)	//���û���Һ���
	{
		preNode->RTag = Thread;	//�Һ������ó�����
		preNode->rChild = node;
	}
	preNode = node;
	InThreading(node->rChild);
}


/*

LTag == 0  lChild ��ָʾ�ڵ������
LTag == 1  lChild ��ָʾ����ǰ��

RTag == 0  rChild ��ָʾ�����Һ���
RTag == 1  rChild ��ָʾ���ĺ��
*/
//ͷ���

void InOrderTraverseThr(Tree T)
{
	Tree P = T->lChild;
	while(P != T)
	{
		//Ѱ�õ�һ�����
		while(P->LTag == Link)
		{
			P=P->lChild;
		}
		printf("%c ",P->data);
		//��ͬ����һ������Ѱ��
		while(P->RTag == Thread && P->rChild != T)
		{
			P = P->rChild;
			printf("%c ",P->data);
		}
		P = P->rChild;
	}
}

void InOrderThreadHead(Tree* H,Tree P)
{
	*H = (Tree)malloc(sizeof(Node));
	if(!(*H))
	{
		exit(-1);
	}
	(*H)->rChild = *H;
	(*H)->RTag = Thread;
	(*H)->LTag = Link;
	if(!P)
	{
		(*H)->lChild = (*H);
	}
	else
	{
		preNode = (*H);
		(*H)->lChild = P;
		InThreading(P);
		//preNode���������һ�����ĵ�ַ
		preNode->rChild = (*H);
		preNode->RTag = Thread;
		(*H)->rChild = preNode;
	}
}

