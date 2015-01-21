#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include <assert.h>
//typedef int ElemType;
/*
#define Sthing a NewName( of Something)	//not a operate sentence ,desposed before compiling

typedef a defined Type  a New TypeName;	//a sentence must ended by ";"
*/
void Debug(int* a,int n,int k);
void Swap(int*a,int* b);

#ifndef BOOL
typedef enum {false,true} BOOL;
#endif

#define TRUE 1
#define FALSE 0
#define OK 1

#ifndef ERROR
	#define ERROR -1
#endif

#define OVERFLOW -2
#define ESC 10

#define CHAR 1
#ifdef CHAR
	typedef char ElemType;
	typedef char TElemType;
#else
	typedef int ElemType;
	typedef int TElemType;
#endif


typedef int status;

#define STACK_INIT_SIZE 100
#define	STACK_INCREMENT 100
#define MAX_INIT_SIZE	100



typedef struct _SNode{
	struct _SNode *pre;
	struct _SNode *next;
	ElemType element;
}SNode;

#define TREE 1
#define ThreadTree 1
//#define HufmanTree 0

typedef struct _Node{
	//struct _Node *parent;
	struct _Node *lChild;
	struct _Node *rChild;
	ElemType data;
}BiNode,*BiTree;


//Link == 0 表示链接孩子的指针
//Thread == 1 表示链接线索的指针
typedef enum {Link,Thread} PointerTag;

/*
LTag == 0  lChild 域指示节点的左孩子
LTag == 1  lChild 域指示结点的前驱

RTag == 0  rChild 域指示结点的右孩子
RTag == 1  rChild 域指示结点的后继
*/
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lChild,*rChild;
	PointerTag LTag;
	PointerTag RTag;
}BiThrNode,*BiThrTree;

typedef struct {
	unsigned int iWeight;
	unsigned int iParent,iLChild,iRChild;
}HuffmanNode,*HuffmanTree;
typedef char **HuffmanCode;
/*
#ifdef HufmanTree
	#define  Node HuffmanNode
	#define  Tree HuffmanTree	
#else 
*/
#ifdef ThreadTree
	#define  Node BiThrNode
	#define  Tree BiThrTree
#else ifdef Tree
#define  Node BiNode
#define  Tree BiTree
#endif


/*
typedef struct _StackNode{
	ElemType data;
	int lchild;
	int rchild;
	int parents;
}StackNode;
*/


#endif