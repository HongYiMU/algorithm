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
	//whileѭ������Ѱ���½ڵ�Ĳ���λ�ã�С���������������
	//ѭ��ֹͣ������ֱ��������Ҷλ�á�
	//predecesor��������Ҷ�ĵ�ַ��Ҳ��ѭ��������ѭ������tmp��ǰ�Ρ�
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
	if(predecesor == NULL)		//����ǿ���
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
	if(x->right != NULL)//�����ǰ������Һ�����ô���ĺ�̶������Һ�����
	{
		return TreeMinmum(x);
	}
	//���û���Һ��ӣ�����������һ������������Ľ���ϡ�
	//whileѭ������Ѱ����һ���������Ľ�㡣
	//ѭ��������û�е�����ڵ�����Ǹ����Һ��ӡ�
	//ѭ����ֹ����Ϊ������ڵ���ߵ��������Ǹ��������֧���
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
	if(oldNode->p == NULL)//������滻����Ǹ��ڵ�
	{
		root = newNode;
	}
	else if(oldNode == oldNode->p->left)//������滻������丸�������֧
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
	if(toDel->left == NULL)			//�����ɾ�����������ǿգ��������Һ��ӽ����滻��
	{
		root = Transplant(root,toDel,toDel->right);
	}
	else if (toDel->right == NULL)	//��֮
	{
		root = Transplant(root,toDel,toDel->left);
	}												//��̵�λ�ÿ���ֱ�������Һ��Ӽ̳У�
	else							//����Ƚϸ����ˣ���������滻��ɾ��㣬��Ϊ��̵�����Ϊ�գ�
	{
		successor = TreeMinmum(toDel->right);	//�������������С�������������̡�
		if (successor != NULL && successor->p != toDel)				
		{										//��������������������Խ�
			root = Transplant(root,successor,successor->right);		//
			successor->right = toDel->right;
			successor->right->p = successor;
		}
		root = Transplant(root,toDel,successor);//�ú���滻��ɾ���
		successor->left = toDel->left;			
		successor->left->p = successor;
	}
	return root;
}


