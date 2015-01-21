#include "common.h"
#include "Stack.h"
#include "Queue.h"
#include "RBTree.h"
#include "BinaryTree.h"


//http://blog.csdn.net/v_JULY_v/article/details/6105630
//https://github.com/torvalds/linux/blob/master/lib/rbtree.c
//https://github.com/torvalds/linux/blob/master/include/linux/rbtree_augmented.h
//https://github.com/torvalds/linux/blob/master/include/linux/rbtree.h

BSNODE* TreeInsert(BSNODE* root,BSNODE* node);
BSNODE* NewNode(BSNODE* node);
BSNODE* IterativeTreeSearch(BSNODE* x,int k);
BSNODE* TreeMaxmum(BSNODE* x);
BSNODE* TreeMinmum(BSNODE* x);
BSNODE* TreeSuccesor(BSNODE* x);
BSNODE* TreeDelete(BSNODE* root,BSNODE* toDel);
void TreePrint(BSNODE* root);

void SearchTree();


void SearchTree()
{
	int i,j;
	BSNODE* Root=NULL;
	BSNODE node;
	BSNODE* tmp;
	int toBeInsert[] = {5,2,8,4,1,6,9,15,12,13,11,16,14,10};
	node.key = 10;
	Root = TreeInsert(Root,&node);
	//         10
	//       /	  \
	//   /           \
	//   5           15
	// /  \         /  \
	//2    8       12  16
	//   /    /  \    / \  
	//  1    6    9  11  13
	//               /	  \
	//              10    14
	for(i=0; i<sizeof(toBeInsert)/sizeof(int*); i++)
	{
		BSNODE node;
		node.key = toBeInsert[i];
		Root = TreeInsert(Root,&node);
	}
	for(i=0; i<17; i++)
	{
		tmp = IterativeTreeSearch(Root,i);
		if(tmp)
		{
			printf("\n%d ",tmp->key);//&& tmp->key != 5
			if (tmp->key == 12)
			{
				i = i;
			}
			Root = TreeDelete(Root,tmp);
			printf("=---=");
			for(j=0; j<20; j++)
			{
				tmp = IterativeTreeSearch(Root,j);
				if(tmp)
				{
					printf("%d ",tmp->key);
				}
			}
		}
	}

}

BSNODE* TreeInsert(BSNODE* root,BSNODE* node)
{
	BSNODE *predecesor = NULL,*tmp = root;
	//while循环用来寻找新节点的插入位置，小于向左大于向右走
	//循环停止条件：直到到达树叶位置。
	//predecesor保存了树叶的地址，也是循环过程中循环变量tmp的前任。
	while(tmp != NULL)
	{
		predecesor = tmp;
		if(node->key < tmp->key)
		{
			tmp = tmp->left;
		}
		else 
		{
			tmp = tmp->right;
		}
	}
	node->p = predecesor;
	tmp = NewNode(node);
	if(predecesor == NULL)		//如果是空树
	{
		return tmp;
	}

	else if(node->key < predecesor->key)
	{
		predecesor->left = tmp;
	}
	else
	{
		predecesor->right = tmp;
	}
	return root;
}
BSNODE* NewNode(BSNODE* node)
{
	BSNODE* pNode = (BSNODE*)malloc(sizeof(BSNODE));
	pNode->key = node->key;
	pNode->p = node->p;
	pNode->left = NULL;
	pNode->right = NULL;

	return pNode;
}


BSNODE* IterativeTreeSearch(BSNODE* x,int k)
{
	while(x != NULL && x->key != k)
	{
		if(k < x->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	return x;
}

BSNODE* TreeMinmum(BSNODE* x)
{
	while(x->left != NULL)
	{
		x = x->left;
	}
	return x;
}
BSNODE* TreeMaxmum(BSNODE* x)
{
	while(x->right != NULL)
	{
		x = x->right;
	}
	return x;
}

BSNODE* TreeSuccesor(BSNODE* x)
{
	BSNODE* p;
	if(x->right != NULL)//如果当前结点有右孩子那么他的后继定在其右孩子中
	{
		return TreeMinmum(x);
	}
	//如果没有右孩子，则其后继在下一个被中序遍历的结点上。
	//while循环用来寻找下一个被遍历的结点。
	//循环条件：没有到达根节点或子是父的右孩子。
	//循环截止条件为到达根节点或者到了子树是父结点的左分支结点
	p = x->p;
	while(p != NULL && x == p->right)
	{
		x = p;
		p = p->p;
	}
	return p;
}
static BSNODE* Transplant(BSNODE* root, BSNODE* oldNode,BSNODE* newNode)
{
	if(oldNode->p == NULL)//如果被替换结点是根节点
	{
		root = newNode;
	}
	else if(oldNode == oldNode->p->left)//如果被替换结点是其父结点的左分支
	{
		oldNode->p->left = newNode;
	}
	else
	{
		oldNode->p->right = newNode;
	}
	if(newNode != NULL)
	{
		newNode->p = oldNode->p;
	}

	return root;
}

BSNODE* TreeDelete(BSNODE* root,BSNODE* toDel)
{
	BSNODE* successor;
	if(toDel->left == NULL)			//如果被删除结点的左孩子是空，则用其右孩子将其替换掉
	{
		root = Transplant(root,toDel,toDel->right);
	}
	else if (toDel->right == NULL)	//反之
	{
		root = Transplant(root,toDel,toDel->left);
	}												//后继的位置可以直接由其右孩子继承，
	else							//否则比较复杂了，后继用来替换被删结点，因为后继的左孩子为空，
	{
		successor = TreeMinmum(toDel->right);	//右子树结点中最小的子孙结点是其后继。
		if (successor != NULL && successor->p != toDel)				
		{										//后继右旋操作。右旋可以将
			root = Transplant(root,successor,successor->right);		//
			successor->right = toDel->right;
			successor->right->p = successor;
		}
		root = Transplant(root,toDel,successor);//用后继替换被删结点
		successor->left = toDel->left;			
		successor->left->p = successor;
	}
	return root;
}


