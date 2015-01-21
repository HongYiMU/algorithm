#include "common.h"
#include "Stack.h"
#include "Queue.h"


static BOOL BinTreeLookUp(Node* node, int target);
static Node* BinTreeInsert(Node* node, int data);
static Node* NewNode(int data);
void BinTreePrint(Node* node);
void CreatBiTree(Tree* T);
void PrintTree(Tree T);
void InOrderTraverse(Tree T);
void PreOrderTraverse(Tree T);
void PostOrderTraverse(Tree T);
void LevelOrderTraverse(Tree T);

static void DataStructure()
{
	Tree T=NULL;
	CreatBiTree(&T);

	//BinTreePrint(T);

	printf("\n");
	//InOrderTraverse(T);
	//PreOrderTraverse(T);
	//PostOrderTraverse(T);
	LevelOrderTraverse(T);
	printf("\n");

}


/************************************************************************
非递归遍历：
（1）工作记录中包含两项，其一是递归调用的语句编号，其二是指向根节点的指针，
则当栈顶记录中的指针非空是，应遍历左子树，即指向左子树根的指针进栈；
（2）若栈顶记录中的指针值为空，则应退至上一层，
若是从左子树返回，则应访问当前层即栈顶记录中指针所指的根节点；
（3）若是从右子树返回，则说明当前层的遍历结束，应继续退栈。从另一角度看，
这意味着遍历右子树时不再需要保存当前层的根指针，可直接修改栈顶记录中的指针即可。

递归遍历与非递归遍历的区别：
递归遍历过程由高层进入底层，当底层满足返回条件时从低层返回高层。
非递归遍历过程是将高层的指针逐级保存入栈，通过指针指向进入底层。
当满足返回条件时（到树底）将上一层的栈弹出并进入上一层，然后转向右子树（或左子树）继续遍历。
************************************************************************/

void CreatBiTree(Tree* T)
{
	ElemType ch[100] = "";
	int len;
	int i;
	fgets(ch,100,stdin);
	len = strlen(ch);
	for(i=0; i<len-1; i++)
	{
		//printf("%c ",ch[i]);
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
		else node->rChild = BinTreeInsert(node->rChild,data);
		return node;
	}

}


static Node* NewNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->lChild = NULL;
	newNode->rChild = NULL;
	//newNode->parent = NULL;
	return newNode;
}


void BinTreePrint(Node* node)
{
	if(node == NULL)
	{
		return ;
	}
	//printf("<%c>",node->data);//先序遍历p,l,r
	BinTreePrint(node->lChild);
	//printf("<%c>",node->data);//	中序遍历l,p,r
	BinTreePrint(node->rChild);
	printf("<%c>",node->data);//后序遍历
}


//非递归中序遍历
/************************************************************************
（1）中序遍历左子树；
（2）访问根节点；
（3）中序遍历右子树；

对于任一结点的临时指针指针变量p，
（1）如果p有指向（非空）那么将结点的地址保存入栈并进入他的左孩子。
（2）如果p为空那么出栈访问上一个结点，然后进入右孩子。
导致p为空的情况：
（a）遍历左孩子到了末尾，栈顶保存的是最后一个左孩子;这时打印的是最后一个左孩子。
（b）从左孩子返回，进入右孩子后，右孩子的地址保存到p，但是右孩子为空。
这时打印的是最后一个左孩子(左孩子可能是空)的父节点。
************************************************************************/
void InOrderTraverse2(Tree T)
{
	SqSTACK stack;
	Tree p = T;
	StackInit(&stack);

	while(p!= NULL || !StackIsEmpty(&stack))
	{
		//探寻左子树的底部
		while(p != NULL)
		{
			Push(&stack,p);
			p = p->lChild;
		}
		//左子树已经到底了，打印并探寻右子树
		if(!StackIsEmpty(&stack))
		{
			p = Pop(&stack);
			printf("%c ",p->data);
			p = p->rChild;
		}		
	}
}
void InOrderTraverse(Tree T)
{
	SqSTACK stack;
	Tree p = T;
	StackInit(&stack);

	while(p!= NULL || !StackIsEmpty(&stack))
	{
		if(p != NULL)
		{
			Push(&stack,p);
			p = p->lChild;
		} 
		else
		{
			p = Pop(&stack);
			printf("%c ",p->data);
			p = p->rChild;
		}
	}
	StackDestroy(&stack);
}

//非递归遍历先序遍历
/************************************************************
（1）访问根节点；
（2）先序遍历左子树；
（3）先序遍历右子树；

遍历过程：
定义临时指针变量p指向树节点；
（1）访问根节点打印其值，保存根节点入栈。
（2）进入左子树，左子树即为根节点。进入（1）过程；
（3）
*************************************************************/
void PreOrderTraverse(Tree T)
{
	SqSTACK stack;
	Tree p = T;
	StackInit(&stack);

	while( p || !StackIsEmpty(&stack))
	{
		if(p != NULL)
		{
			printf("-%c-",p->data);
			Push(&stack,p);
			p = p->lChild;
		}
		else
		{
			p = Pop(&stack);
			p = p->rChild;
		}
	}

	StackDestroy(&stack);

}



//非递归遍历后序遍历
//http://www.cnblogs.com/dolphin0520/archive/2011/08/25/2153720.html
/************************************************************
若二叉树为空，则空操作；否则
（1）后序遍历左子树；
（2）后序遍历右子树；
（3）访问根节点；

遍历过程：

要保证根结点在左孩子和右孩子访问之后才能访问，因此
(1)对于任一结点P，先将其入栈。
a)如果P不存在左孩子和右孩子，则可以直接访问它；
b)或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。

(2)若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，
左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
*************************************************************/
void PostOrderTraverse(Tree T)
{
	SqSTACK stack;
	Tree p = T;
	Tree pre = NULL;
	StackInit(&stack);
	Push(&stack,p);
	while(!StackIsEmpty(&stack))
	{
		p = StackGetTop(&stack);
		if((p->lChild == NULL && p->rChild == NULL) ||\
			(pre != NULL &&(p->rChild == pre || p->lChild == pre)))
		{
			printf("<%c>",p->data);
			Pop(&stack);
			pre = p;
		}
		else
		{
			if (p->rChild != NULL)
			{
				Push(&stack,p->rChild);
			}
			if (p->lChild != NULL)
			{
				Push(&stack,p->lChild);
			}	
			p = p->lChild;
		}
	}

	StackDestroy(&stack);

}



/************************************************************************
层序遍历：
************************************************************************/

void LevelOrderTraverse(Tree T)
{
	SQueue queue;
	Tree p = T;
	QueueInit(&queue);
	QueueWrite(&queue,p);

	while(!QueueIsEmpty(&queue))
	{
		if(QueueRead(&queue,&p)<0)
		{
			printf("empty!!!\n");
			//break;
		}
		printf("<%c>",p->data);
		if(p->lChild)
		{
			QueueWrite(&queue,p->lChild);
		}
		if(p->rChild)
		{
			QueueWrite(&queue,p->rChild);
		}
	}
	QueueDestroy(&queue);
}


