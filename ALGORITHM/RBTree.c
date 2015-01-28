//
// �������ԣ�
// 1.ÿ���ڵ���Ǻ�ɫ�ģ����Ǻ�ɫ�ġ�
// 2.���ڵ��Ǻ�ɫ�ġ�
// 3.ÿ��Ҷ��㣨NIL���Ǻ�ɫ�ġ�
// 4.���һ������Ǻ�ɫ�ģ������������ӽ�㶼�Ǻ�ɫ�ġ�
// 5.��ÿ����㣬�Ӹý�㵽�����к��Ҷ���ļ�·����
// ��������ͬ��Ŀ�ĺ�ɫ��㡣
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
	//��������
	//              11
	// 		   2      14
	// 	    1    7       15
	// 	       5   8
	// 		 4
	///////////////////////////////////////
	///////////////////////////////////////
	//������� 
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

//������������ҽ��  
//----------------------------------------------------  
//rb_search_auxiliary������  
//rb_node_t* rb_search�������ҵ��Ľ��  
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

//��������rb_search_auxiliary���ҽ��  
RB_NODE* RbSearch(int key, RB_NODE* root)  
{  
	return RbSearchAuxiliary(key, root, NULL);  
}  


RB_NODE* RbInsert(RB_NODE* head, RB_NODE* node)
{
	RB_NODE *tmp = head;
	RB_NODE *pre = NULL;
	//�������Ĳ��붯����Ҫ���ҵ�����λ��
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


//������
//�Һ��Ӻ�top��λ�õ���,top��Ϊright������
//top��������С��Ȼ��top������
//�Һ��ӵ����Ӵ���topС���Һ��ӣ�����ת����Ϊtop���Һ���
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

// ���� --- ����������ת�Ƶ�����λ�ã�ԭ���ĸ���Ϊ�µĸ����Һ���
//��Сֵa�����ֵr������
//�м�����:x--С��ԭ����y������ԭ����������x��
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
// �������ԣ�
// 1.ÿ���ڵ���Ǻ�ɫ�ģ����Ǻ�ɫ�ġ�
// 2.���ڵ��Ǻ�ɫ�ġ�
// 3.ÿ��Ҷ��㣨NIL���Ǻ�ɫ�ġ�
// 4.���һ������Ǻ�ɫ�ģ������������ӽ�㶼�Ǻ�ɫ�ġ�
// 5.��ÿ����㣬�Ӹý�㵽�����к��Ҷ���ļ�·����
// ��������ͬ��Ŀ�ĺ�ɫ��㡣
//
//���������Ǹ���㣬����ԭ���ǿ����������ֻ��Υ������2�����ֱ�ӰѴ˽��ͿΪ��ɫ��
//�������Ľ��ĸ�����Ǻ�ɫ�����ڴ˲���Υ������2������4�������û�б��ƻ������Դ�ʱʲôҲ������
//
//������Ҫ�޸��������Ȼ�ǲ���Ľ��ĸ�����Ǻ�ɫ���游����Ǻ�ɫ
//�����޸����1�������ǰ���ĸ�����Ǻ�ɫ���游������һ���ӽ�㣨�����㣩�Ǻ�ɫ
//�����޸����2����ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ,����ڵ��Ǻ�ɫ����ǰ�ڵ����丸�ڵ������
//�����޸����3����ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ,����ڵ��Ǻ�ɫ����ǰ�ڵ����丸�ڵ������
//
static RB_NODE* InsertFixup(RB_NODE* head, RB_NODE* node)
{
	RB_NODE *parnt, *grdparnt,*uncle, *tmp;
	while((parnt = node->p) && parnt->color == RED)
	{
		//1.���z.p(z�ĸ����)���丸��������
		//(1)���丸�����Һ�����Ϊy
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
				// case 1:z.pΪRED
				//	z.p���丸��������
				//	yΪz.p�����ֵ�
				//	yΪRED������4��
				//	��z.p��y����ΪBLACK
				//	��z.p.p��ΪRED
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
					//z.pΪRED
					//	z.p���丸�ڵ������
					//	yΪz.p�����ֵ�
					//	yΪBLACK &&  z��z.p���Һ���
					//	����������4��
					//	  z = z.p//ָ������
					//	  ����
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
//����滻����u��v�滻����
//���1����������Ǹ�����ô����ַָ��v
//���2�����������һ�����ӣ�
//���3�����������һ���Һ���
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
//ɾ���������ӡ��Һ��ӡ�������滻��ɾ���Ľ�㡣Ȼ����ݹ����������������
// ����Ϊ�վ����Һ��ӣ��Һ���Ϊ�վ������ӣ����������Ӿ��ú�̡�
// 
// ��������ԣ�
// 1.ÿ���ڵ���Ǻ�ɫ�ģ����Ǻ�ɫ�ġ�
// 2.���ڵ��Ǻ�ɫ�ġ�
// 3.ÿ��Ҷ��㣨NIL���Ǻ�ɫ�ġ�
// 4.���һ������Ǻ�ɫ�ģ������������ӽ�㶼�Ǻ�ɫ�ġ�
// 5.��ÿ����㣬�Ӹý�㵽�����к��Ҷ���ļ�·����
// ��������ͬ��Ŀ�ĺ�ɫ��㡣
//
// //���y(z)����ɾ��㣩�Ǻ�ɫ����y��ɾ�����ƶ�ʱ�����������Ȼ���֣�ԭ������:
// 1.���еĺڸ�û�б仯��
// 2.�������������ڵĺ��㡣��Ϊy������ռ����z��λ�ã��ڿ��ǵ�z����ɫ������y����λ��
// ���������������ڵĺ��㡣���⣬���y����z���Һ��ӣ���y��ԭ�Һ���x����y.���y�Ǻ�ɫ��
// ��xһ���Ǻ�ɫ�������x���y������ʹ�����������ڡ�
// 3.���y�Ǻ�ɫ���Ͳ������Ǹ��ڵ㣬���Ը��ڵ��Ծ��Ǻ�ɫ��
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
			x->p = y;		//������������
		}
		else				//�����������ﱲ���ﱲ�ĺ�
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
		y->color = z->color;//�滻֮����ɫ��ԭ
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
	//printf("<%c>",node->data);//�������p,l,r
	TreePrint(node->left);
	printf("<%d>",node->key);//	�������l,p,r
	TreePrint(node->right);
	//printf("<%c>",node->data);//�������
}

