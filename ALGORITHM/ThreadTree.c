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
//http://zh.wikipedia.org/wiki/二叉树

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
	//printf("<%c>",node->data);//先序遍历p,l,r
	BinTreePrint(node->lChild);
	printf("<%c>",node->data);//	中序遍历l,p,r
	BinTreePrint(node->rChild);
	//printf("<%c>",node->data);//后序遍历
}

//建立线索二叉树

Node* preNode = NULL;//全局变量，指向访问过的上一个结点。
void InThreading(Node* node)
{
	if(node == NULL)
	{
		return ;
	}
	InThreading(node->lChild);
	if(!node->lChild)	//如果没有左孩子设置成线索，
	{
		node->LTag = Thread;	//左孩子设置成线索
		node->lChild = preNode;	//前驱是上一个结点
	}
	if(!preNode->rChild)	//如果没有右孩子
	{
		preNode->RTag = Thread;	//右孩子设置成线索
		preNode->rChild = node;
	}
	preNode = node;
	InThreading(node->rChild);
}


/*

LTag == 0  lChild 域指示节点的左孩子
LTag == 1  lChild 域指示结点的前驱

RTag == 0  rChild 域指示结点的右孩子
RTag == 1  rChild 域指示结点的后继
*/
//头结点

void InOrderTraverseThr(Tree T)
{
	Tree P = T->lChild;
	while(P != T)
	{
		//寻访第一个结点
		while(P->LTag == Link)
		{
			P=P->lChild;
		}
		printf("%c ",P->data);
		//如同链表一样挨个寻访
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
		//preNode保存了最后一个结点的地址
		preNode->rChild = (*H);
		preNode->RTag = Thread;
		(*H)->rChild = preNode;
	}
}

