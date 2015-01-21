#include "stdio.h"
#include <string.h>
#include <stdlib.h>
  
//二叉树的练习  
  
  
typedef struct BiTNode  
{  
    char data;   /*结点的数据域*/  
    struct BiTNode *lchild , *rchild;  /*指向左孩子和右孩子*/  
} BiTNode , *BiTree;  
  
/*创建一棵二叉树*/  
void CreatBiTree(BiTree *T)  
{  
    char c;  
   
    //c = getchar();  
    c= fgetc(stdin);
    fflush(stdin);
    printf("get = %c\n",c);  
    if(c == 10)   
        *T = NULL;  
    else  
    {  
       *T = (BiTNode * )malloc(sizeof(BiTNode));  /*创建根结点*/  
       (*T)->data = c;                   /*向根结点中输入数据*/  
       CreatBiTree(&((*T)->lchild));     /*递归地创建左子树*/  
       CreatBiTree(&((*T)->rchild));     /*递归地创建右子树*/  
    }  
}  
  
/*访问二叉树结点，输出包含D字符结点位于二叉树中的层数*/  
void visit(char c,int level)  
{  
     if(c == 'D')  
        printf("%c is at %d lever of BiTree\n",c,level);  
}  
  
/*遍历二叉树*/  
//先序  
void PreOrderTraverse(BiTree T,int level)  
{  
    if(T)  
    {   /*递归结束条件，T为空*/  
        printf("node: %c, level: %d\n",T->data,level);  
        //visit(T->data,level);  /*访问根结点*/  
        PreOrderTraverse(T->lchild,level+1);  /*先序遍历T的左子树*/  
        PreOrderTraverse(T->rchild,level+1);  /*先序遍历T的右子数*/  
    }  
}  
//中序  
void InOrderTraverse(BiTree T,int level)  
{  
    if(T)  
    {   /*递归结束条件，T为空*/  
        InOrderTraverse(T->lchild,level+1);  /*先序遍历T的左子树*/  
        printf("node: %c, level: %d\n",T->data,level);  
        InOrderTraverse(T->rchild,level+1);  /*先序遍历T的右子数*/  
    }  
}  
//后序  
void PostOrderTraverse(BiTree T,int level)  
{  
    if(T)  
    {   /*递归结束条件，T为空*/  
        PostOrderTraverse(T->lchild,level+1);  /*先序遍历T的左子树*/  
        PostOrderTraverse(T->rchild,level+1);  /*先序遍历T的右子数*/  
        printf("node: %c, level: %d\n",T->data,level);  
    }  
}  
//统计二叉树叶子节点数  
int CountLeaf(BiTree T)  
{  
    static int count = 0;  
  
    if (T)  
    {  
        count = CountLeaf(T->lchild);  
        if ((T->lchild == NULL) && (T->rchild == NULL))  
        {  
            count ++;  
        }  
        count = CountLeaf(T->rchild);  
    }  
    return count;  
}  
//求二叉树的深度  
int TreeDepth(BiTree T)  
{  
    static int count = 0;  
      
    if (T)  
    {  
        count++;  
        count = TreeDepth(T->lchild);  
        count = TreeDepth(T->rchild);  
    }  
    return count;  
}  
  
int main(int argc, char* argv[])  
{  
   int level = 1;  
   int Node_num = 0,Depth_num = 0;  
   BiTree T = NULL;  /*最开始T指向空*/  
     
   CreatBiTree(&T);             //创建二叉树，先画出树形图，根据图进行输入创建  
   printf("\n先序遍历：\n");  
   PreOrderTraverse(T,level);   //遍历二叉树，找到包含D字符结点位于二叉树中的层数  
   printf("\n中序遍历：\n");  
   InOrderTraverse(T,level);    //遍历二叉树，找到包含D字符结点位于二叉树中的层数  
   printf("\n后序遍历：\n");  
   PostOrderTraverse(T,level);  //遍历二叉树，找到包含D字符结点位于二叉树中的层数  
      
   Node_num = CountLeaf(T);  
   Depth_num = TreeDepth(T);  
   printf("\nNode_num = %d, Depth_num = %d\n",Node_num,Depth_num);  
   getchar();
   return 0;
}  
