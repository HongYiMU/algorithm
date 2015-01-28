//
// 五条属性：
// 1.每个节点或是红色的，或是黑色的。
// 2.根节点是黑色的。
// 3.每个叶结点（NIL）是黑色的。
// 4.如果一个结点是红色的，则它的两个子结点都是黑色的。
// 5.对每个结点，从该结点到其所有后代叶结点的简单路径上
// 均包含相同数目的黑色结点。
//

//http://blog.csdn.net/v_JULY_v/article/details/6105630
//https://github.com/torvalds/linux/blob/master/lib/rbtree.c
//https://github.com/torvalds/linux/blob/master/include/linux/rbtree_augmented.h
//https://github.com/torvalds/linux/blob/master/include/linux/rbtree.h

#include "common.h"
#include "RBTree.h"

static RB_NODE* RbSearch(int key, RB_NODE* root);
static RB_NODE* RbInsert(RB_NODE* head, RB_NODE* node);
static RB_NODE* InsertFixup(RB_NODE *,RB_NODE *);
static RB_NODE* LeftRotate(RB_NODE* head, RB_NODE* node);
static RB_NODE* RightRotate(RB_NODE* head, RB_NODE* node);
static RB_NODE* RbTransplant(RB_NODE* head,RB_NODE* u,RB_NODE* v);

static RB_NODE* RbDeleteFixup(RB_NODE* head, RB_NODE* x);
static RB_NODE* RbDelete(RB_NODE* head, RB_NODE* z);
static void TreePrint(RB_NODE* head);
static void LevelOrderWalk(RB_NODE* node);

void PrintT(RB_NODE* head)
{
	RB_NODE *left=NULL, *right=NULL;
	RB_NODE *left1=NULL,*left2=NULL,*right1=NULL,*right2=NULL;
	RB_NODE *left31=NULL,*left32=NULL,*right31=NULL,*right32=NULL,*left33=NULL,*left34=NULL,*right33=NULL,*right34=NULL;
	if(head)
	{
		left=head->left;
		right=head->right;
	}

	if(left)
		printf("[%d]",left->key);
	if(head)
	printf("[%d]",head->key);
	if(right)
		printf("[%d]",right->key);
	printf("\n-----\n");

	if(left)
	{
		left1 = left->left;
		left2 = left->right;
	}
	if(right)
	{
		right1 = right->left;
		right2 = right->right;
	}
	if(left1)
		printf("[%d]",left1->key);
	if(left2)
		printf("[%d]",left2->key);
	if(right1)
		printf("[%d]",right1->key);
	if(right2)
		printf("[%d]",right2->key);
	printf("\n-----\n");

	if(left1)
	{
		left31 = left1->left;
		left32 = left1->right;
	}
	if(left2)
	{
		left33 = left2->left;
		left34 = left2->right;
	}
	if(right1)
	{
		right31 = right1->left;
		right32 = right1->right;
	}
	if(right2)
	{
		right33 = right2->left;
		right34 = right2->right;
	}
	if(left31)
		printf("[%d]",left31->key);	
	if(left32)
		printf("[%d]",left32->key);
	if(left33)
		printf("[%d]",left33->key);
	if(left34)
		printf("[%d]",left34->key);
	if(right31)
		printf("[%d]",right31->key);
	if(right32)
		printf("[%d]",right32->key);
	if(right33)
		printf("[%d]",right33->key);
	if(right34)
		printf("[%d]",right34->key);
	printf("\n-----\n");
}

void RBTree()
{

	///////////////////////////////////////
	//二叉树：
	//              11
	// 		   2      14
	// 	    1    7       15
	// 	       5   8
	// 		 4
	///////////////////////////////////////
	///////////////////////////////////////
	//红黑树： 
	//              7
	// 		   2        11
	// 	    1    5    8    14
	// 	       4  6    9  13  15
	// 		 
	///////////////////////////////////////
	int toBeInsert[] = {11,2,14,1,7,15,5,8,9,4,13,6};
	int i;
	RB_NODE *head = NULL;
	RB_NODE * tmp = NULL;
	RB_NODE* node;
	for(i=0; i<sizeof(toBeInsert)/sizeof(int); i++)
	{
		node = (RB_NODE*)malloc(sizeof(RB_NODE));
		node->key = toBeInsert[i];
		head = RbInsert(head, node);
	}
	//TreePrint(head);
	PrintT(head);
	printf("\n==========\n");
	for(i=0; i<sizeof(toBeInsert)/sizeof(int); i++)
	{
		tmp = RbSearch(toBeInsert[i],head);
		if(tmp)
		{
			printf("%d ",tmp->key);
			head = RbDelete(head, tmp);
			PrintT(head);
			//TreePrint(head);
			printf("\n");
		}
	}
	printf("\n");

}

//三、红黑树查找结点  
//----------------------------------------------------  
//rb_search_auxiliary：查找  
//rb_node_t* rb_search：返回找到的结点  
//----------------------------------------------------  
static RB_NODE* RbSearchAuxiliary(int key, RB_NODE* root, RB_NODE** pre)  
{  
	RB_NODE *node = root, *parent = NULL;
	int ret;

	while(node)
	{
		parent = node;
		ret = node->key - key;  
		if (0 < ret)
		{
			node = node->left;  
		}
		else if (0 > ret)
		{  
			node = node->right;
		}  
		else
		{
			return node;  
		}
	}

	if (pre)
	{
		*pre = parent;
	}

	return NULL;
}

//返回上述rb_search_auxiliary查找结果  
RB_NODE* RbSearch(int key, RB_NODE* root)  
{  
	return RbSearchAuxiliary(key, root, NULL);  
}  


RB_NODE* RbInsert(RB_NODE* head, RB_NODE* node)
{
	RB_NODE *tmp = head;
	RB_NODE *pre = NULL;
	//二叉树的插入动作需要先找到插入位置
	while(tmp != NULL)
	{
		pre = tmp;
		if(node->key < tmp->key)
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
		head = node;
	}
	else if(node->key < pre->key)
	{
		pre->left = node;
	}
	else
	{
		pre->right = node;
	}
	node->p = pre;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;
	head = InsertFixup(head,node);
	return head;
}


//左旋，
//右孩子和top的位置调换,top成为right的左孩子
//top的左孩子最小依然是top的左孩子
//右孩子的左孩子大于top小于右孩子，经过转换成为top的右孩子
//
RB_NODE* LeftRotate(RB_NODE* head, RB_NODE* top)
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

// 右旋 --- 将根的左孩子转移到根的位置，原来的根成为新的根的右孩子
//最小值a和最大值r都不变
//中间数据:x--小于原来根y，大于原来根的左孩子x。
//        y        x     
//      x   r -->a   y   
//     a b          b r
//
RB_NODE* RightRotate(RB_NODE* head, RB_NODE* y)
{
	RB_NODE *x = y->left;
	y->left = x->right;
	if(x->right != NULL)
	{
		x->right->p = y;
	}
	x->p = y->p;
	if(y->p == NULL)
	{
		head = x;
	}
	else if(y == y->p->left)
	{
		x->p->left = x;
	}
	else
	{
		x->p->left = x;
	}
	x->right = y;
	y->p = x;
	return head;

}
//
// 五条属性：
// 1.每个节点或是红色的，或是黑色的。
// 2.根节点是黑色的。
// 3.每个叶结点（NIL）是黑色的。
// 4.如果一个结点是红色的，则它的两个子结点都是黑色的。
// 5.对每个结点，从该结点到其所有后代叶结点的简单路径上
// 均包含相同数目的黑色结点。
//
//如果插入的是根结点，由于原树是空树，此情况只会违反性质2，因此直接把此结点涂为黑色；
//如果插入的结点的父结点是黑色，由于此不会违反性质2和性质4，红黑树没有被破坏，所以此时什么也不做。
//
//出现需要修复的情况必然是插入的结点的父结点是红色，祖父结点是黑色
//插入修复情况1：如果当前结点的父结点是红色且祖父结点的另一个子结点（叔叔结点）是红色
//插入修复情况2：当前节点的父节点是红色,叔叔节点是黑色，当前节点是其父节点的右子
//插入修复情况3：当前节点的父节点是红色,叔叔节点是黑色，当前节点是其父节点的左子
//
static RB_NODE* InsertFixup(RB_NODE* head, RB_NODE* node)
{
	RB_NODE *parnt, *grdparnt,*uncle, *tmp;
	while((parnt = node->p) && parnt->color == RED)
	{
		//1.如果z.p(z的父结点)是其父结点的左孩子
		//(1)将其父结点的右孩子设为y
		//	z.p<z.p.p<y
		grdparnt = parnt->p;
		if(grdparnt->left == parnt)
		{
			uncle = grdparnt->right;
			if(uncle && uncle->color == RED)
			{
				parnt->color = BLACK;
				uncle->color = BLACK;
				grdparnt->color = RED;
				node = grdparnt;
				// case 1:z.p为RED
				//	z.p是其父结点的左孩子
				//	y为z.p的右兄弟
				//	y为RED（规则4）
				//	将z.p和y都置为BLACK
				//	将z.p.p置为RED
			}
			else 
			{
				if(node == parnt->right)
				{
					head = LeftRotate(head,parnt);
					tmp = parnt;
					parnt = node;
					node = tmp;
					//case2:
					//z.p为RED
					//	z.p是其父节点的左孩子
					//	y为z.p的右兄弟
					//	y为BLACK &&  z是z.p的右孩子
					//	　　（规则4）
					//	  z = z.p//指针上移
					//	  左旋
				}
				parnt->color = BLACK;	//case 3
				grdparnt->color = RED;
			    head = RightRotate(head,grdparnt);
			}
		}
		else if (grdparnt->right == parnt)
		{
			uncle = grdparnt->left;
			if(uncle && uncle->color == RED)
			{
				parnt->color = BLACK;
				uncle->color = BLACK;
				grdparnt->color = RED;
				node = grdparnt;
			}
			else 
			{
				if(node == parnt->left)
				{
					head = RightRotate(head,parnt);
					tmp = parnt;
					parnt = node;
					node = tmp;
				}
				parnt->color = BLACK;	//case 3
				grdparnt->color = RED;
				head = LeftRotate(head,grdparnt);
			}
		}
	}
	head->color = BLACK;
	return head;
}



static RB_NODE* TreeMinmum(RB_NODE* x)
{
	while(x->left != NULL)
	{
		x = x->left;
	}
	return x;
}
//
//结点替换：将u用v替换掉。
//情况1：被换结点是根，那么根地址指向v
//情况2：被换结点是一个左孩子，
//情况3：被换结点是一个右孩子
static RB_NODE* RbTransplant(RB_NODE* head,RB_NODE* u,RB_NODE* v)
{
	if(u->p == NULL)
	{
		head = v;
	}
	else if ( u == u->p->left)
	{
		u->p->left = v;
	}
	else
	{
		u->p->right = v;	
	}
	if(v)
	{
		v->p = u->p;
	}
	
	return head;
}

///////////////////////////////////////////////////////////////////////////////////////////
//删除：用左孩子、右孩子、后继来替换被删除的结点。然后根据规则进行重新修整。
// 左孩子为空就用右孩子，右孩子为空就用左孩子，有两个孩子就用后继。
// 
// 红黑树属性：
// 1.每个节点或是红色的，或是黑色的。
// 2.根节点是黑色的。
// 3.每个叶结点（NIL）是黑色的。
// 4.如果一个结点是红色的，则它的两个子结点都是黑色的。
// 5.对每个结点，从该结点到其所有后代叶结点的简单路径上
// 均包含相同数目的黑色结点。
//
// //如果y(z)（被删结点）是红色，当y被删除或移动时，红黑性质仍然保持，原因如下:
// 1.树中的黑高没有变化。
// 2.不存在两个相邻的红结点。因为y在树中占据了z的位置，在考虑到z的颜色，树中y的新位置
// 不可能有两个相邻的红结点。另外，如果y不是z的右孩子，则y的原右孩子x代替y.如果y是红色，
// 则x一定是黑色，因此用x替代y不可能使两个红结点相邻。
// 3.如果y是红色，就不可能是根节点，所以根节点仍旧是黑色。
///////////////////////////////////////////////////////////////////////////////////////////
static RB_NODE* RbDelete(RB_NODE* head, RB_NODE* z)
{
	RB_NODE* y = z;
	RB_NODE* x;
	COLOR yOrgClr = y->color;
	if(z->left == NULL)
	{
		x = z->right;
		head = RbTransplant(head,z,z->right);
	}
	else if(z->right == NULL)
	{
		x = z->left;
		head = RbTransplant(head,z,z->left);
	}
	else
	{
		y = TreeMinmum(z->right);
		yOrgClr = y->color;
		x = y->right;
		if(y->p == z)
		{
			if(x)
			x->p = y;		//如果后继是其子
		}
		else				//如果后继是其孙辈或孙辈的后辈
		{
			head = RbTransplant(head,y,y->right);
			y->right = z->right;
			y->right->p = y;
		}
		head = RbTransplant(head,z,y);
		y->left = z->left;
		if(y->left)
		{
			y->left->p = y;
		}
		y->color = z->color;//替换之后，颜色复原
	}
	free(z);
	if(yOrgClr == BLACK)
	{
		head = RbDeleteFixup(head,x);
	}
	return head;
}
//
//
static RB_NODE* RbDeleteFixup(RB_NODE* head, RB_NODE* x)
{
	while(x && x->p != NULL && x->color == BLACK)
	{
		RB_NODE* w;
		if(x == x->p->left)	//
		{
			w = x->p->right;
			if(w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				head = LeftRotate(head,x->p);
				w = x->p->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else 
			{
				if(w->right->color)
				{
					w->left->color = BLACK;
					w->color = RED;
					head = RightRotate(head,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				head = LeftRotate(head,x->p);
				x = head;
			}
			
		}
		else
		{
			w = x->p->left;
			if(w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				head = RightRotate(head,x->p);
				w = x->p->left;
			}
			if(w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else 
			{
				if(w->left->color)
				{
					w->right->color = BLACK;
					w->color = RED;
					head = LeftRotate(head,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				head = RightRotate(head,x->p);
				x = head;
			}
		}
	}
	if(x)
	x->color = BLACK;
	return head;
}

static void TreePrint(RB_NODE* node)
{
	if(node == NULL)
	{
		return ;
	}
	//printf("<%c>",node->data);//先序遍历p,l,r
	TreePrint(node->left);
	printf("<%d>",node->key);//	中序遍历l,p,r
	TreePrint(node->right);
	//printf("<%c>",node->data);//后序遍历
}

