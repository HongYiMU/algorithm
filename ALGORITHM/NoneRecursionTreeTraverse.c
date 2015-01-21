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
�ǵݹ������
��1��������¼�а��������һ�ǵݹ���õ�����ţ������ָ����ڵ��ָ�룬
��ջ����¼�е�ָ��ǿ��ǣ�Ӧ��������������ָ������������ָ���ջ��
��2����ջ����¼�е�ָ��ֵΪ�գ���Ӧ������һ�㣬
���Ǵ����������أ���Ӧ���ʵ�ǰ�㼴ջ����¼��ָ����ָ�ĸ��ڵ㣻
��3�����Ǵ����������أ���˵����ǰ��ı���������Ӧ������ջ������һ�Ƕȿ���
����ζ�ű���������ʱ������Ҫ���浱ǰ��ĸ�ָ�룬��ֱ���޸�ջ����¼�е�ָ�뼴�ɡ�

�ݹ������ǵݹ����������
�ݹ���������ɸ߲����ײ㣬���ײ����㷵������ʱ�ӵͲ㷵�ظ߲㡣
�ǵݹ���������ǽ��߲��ָ���𼶱�����ջ��ͨ��ָ��ָ�����ײ㡣
�����㷵������ʱ�������ף�����һ���ջ������������һ�㣬Ȼ��ת������������������������������
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
	//printf("<%c>",node->data);//�������p,l,r
	BinTreePrint(node->lChild);
	//printf("<%c>",node->data);//	�������l,p,r
	BinTreePrint(node->rChild);
	printf("<%c>",node->data);//�������
}


//�ǵݹ��������
/************************************************************************
��1�����������������
��2�����ʸ��ڵ㣻
��3�����������������

������һ������ʱָ��ָ�����p��
��1�����p��ָ�򣨷ǿգ���ô�����ĵ�ַ������ջ�������������ӡ�
��2�����pΪ����ô��ջ������һ����㣬Ȼ������Һ��ӡ�
����pΪ�յ������
��a���������ӵ���ĩβ��ջ������������һ������;��ʱ��ӡ�������һ�����ӡ�
��b�������ӷ��أ������Һ��Ӻ��Һ��ӵĵ�ַ���浽p�������Һ���Ϊ�ա�
��ʱ��ӡ�������һ������(���ӿ����ǿ�)�ĸ��ڵ㡣
************************************************************************/
void InOrderTraverse2(Tree T)
{
	SqSTACK stack;
	Tree p = T;
	StackInit(&stack);

	while(p!= NULL || !StackIsEmpty(&stack))
	{
		//̽Ѱ�������ĵײ�
		while(p != NULL)
		{
			Push(&stack,p);
			p = p->lChild;
		}
		//�������Ѿ������ˣ���ӡ��̽Ѱ������
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

//�ǵݹ�����������
/************************************************************
��1�����ʸ��ڵ㣻
��2�����������������
��3�����������������

�������̣�
������ʱָ�����pָ�����ڵ㣻
��1�����ʸ��ڵ��ӡ��ֵ��������ڵ���ջ��
��2����������������������Ϊ���ڵ㡣���루1�����̣�
��3��
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



//�ǵݹ�����������
//http://www.cnblogs.com/dolphin0520/archive/2011/08/25/2153720.html
/************************************************************
��������Ϊ�գ���ղ���������
��1�����������������
��2�����������������
��3�����ʸ��ڵ㣻

�������̣�

Ҫ��֤����������Ӻ��Һ��ӷ���֮����ܷ��ʣ����
(1)������һ���P���Ƚ�����ջ��
a)���P���������Ӻ��Һ��ӣ������ֱ�ӷ�������
b)����P�������ӻ����Һ��ӣ����������Ӻ��Һ��Ӷ��ѱ����ʹ��ˣ���ͬ������ֱ�ӷ��ʸý�㡣

(2)�������������������P���Һ��Ӻ�����������ջ�������ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ��
�������Һ���ǰ�汻���ʣ����Ӻ��Һ��Ӷ��ڸ����ǰ�汻���ʡ�
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
���������
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


