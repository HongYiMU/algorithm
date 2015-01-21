#include "common.h"
#include "RBTree.h"

//http://blog.csdn.net/v_JULY_v/article/details/6105630
//https://github.com/torvalds/linux/blob/master/lib/rbtree.c
//https://github.com/torvalds/linux/blob/master/include/linux/rbtree_augmented.h
//https://github.com/torvalds/linux/blob/master/include/linux/rbtree.h

//static void 
//              11
// 		   2      14
// 	    1    7       15
// 	       5   8
// 		 4

static RB_NODE* RBTInsert(RB_NODE* head, RB_NODE* RBNode);
static void InsertFixup();
void LeftRotate(RB_NODE* head, RB_NODE* RBNode);
void RightRotate(RB_NODE* head, RB_NODE* RBNode);
void RBTree()
{
	RB_NODE* head = NULL;
	
}

RB_NODE* RBTInsert(RB_NODE* head, RB_NODE* RBNode)
{
	RB_NODE *tmp = head;
	RB_NODE *pre = NULL;
	//二叉树的插入动作需要先找到插入位置
	while(tmp != NULL)
	{
		pre = tmp;
		if(RBNode->key < tmp->key)
		{
			tmp = tmp->left;
		}
		else
		{
			tmp = tmp->right;
		}
	}
	if(pre == NULL)
	{
		head = RBNode;
	}
	else if(RBNode->key < pre->key)
	{
		pre->left = RBNode;
	}
	else
	{
		pre->right = RBNode;
	}
	RBNode->p = pre;
	RBNode->color = RED;
	RBNode->left = NULL;
	RBNode->right = NULL;

	return head;
}


//左旋，
//右孩子和top的位置调换,top成为right的左孩子
//top的左孩子最小依然是top的左孩子
//右孩子的左孩子大于top小于右孩子，经过转换成为top的右孩子
//
void LeftRotate(RB_NODE* head, RB_NODE* top)
{
	RB_NODE* right = top->right;
	top->right = right->left;
	if(right->left != NULL)
	{
		right->left->p = top;
	}
	right->p = top->p;
	if(top->p == NULL)
	{
		head = right;
	}
	else if(top == top->p->left)
	{
		top->p->left = right;
	}
	else if(top == top->p->right)
	{
		top->p->right = right;
	}
	right->left = top;
	top->p = right;
	return head;
}

// 右旋
//将top和其左孩子兑换，top成为其左孩子的右孩子
//top的父结点成为左孩子的父结点。
//左孩子的右孩子成为top的左孩子。left->left < left < left->rigth <top < top->right
void RightRotate(RB_NODE* head, RB_NODE* top)
{
	RB_NODE *left = top->left;
	top->left = left->left;
	if(left->left != NULL)
	{
		left->left->p = top;
	}
	left->p = top->p;
	if(top->p == NULL)
	{
		head = left;
	}
	else if(top == top->p->left)
	{
		top->p->left = left;
	}
	else
	{
		top->p->right = left;
	}
	left->right = top;
	top->p = left;
	return head;

}

void void InsertFixup()
{

}
