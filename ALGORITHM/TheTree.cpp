#include "stdio.h"
#include <string.h>
#include <stdlib.h>
  
//����������ϰ  
  
  
typedef struct BiTNode  
{  
    char data;   /*����������*/  
    struct BiTNode *lchild , *rchild;  /*ָ�����Ӻ��Һ���*/  
} BiTNode , *BiTree;  
  
/*����һ�ö�����*/  
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
       *T = (BiTNode * )malloc(sizeof(BiTNode));  /*���������*/  
       (*T)->data = c;                   /*����������������*/  
       CreatBiTree(&((*T)->lchild));     /*�ݹ�ش���������*/  
       CreatBiTree(&((*T)->rchild));     /*�ݹ�ش���������*/  
    }  
}  
  
/*���ʶ�������㣬�������D�ַ����λ�ڶ������еĲ���*/  
void visit(char c,int level)  
{  
     if(c == 'D')  
        printf("%c is at %d lever of BiTree\n",c,level);  
}  
  
/*����������*/  
//����  
void PreOrderTraverse(BiTree T,int level)  
{  
    if(T)  
    {   /*�ݹ����������TΪ��*/  
        printf("node: %c, level: %d\n",T->data,level);  
        //visit(T->data,level);  /*���ʸ����*/  
        PreOrderTraverse(T->lchild,level+1);  /*�������T��������*/  
        PreOrderTraverse(T->rchild,level+1);  /*�������T��������*/  
    }  
}  
//����  
void InOrderTraverse(BiTree T,int level)  
{  
    if(T)  
    {   /*�ݹ����������TΪ��*/  
        InOrderTraverse(T->lchild,level+1);  /*�������T��������*/  
        printf("node: %c, level: %d\n",T->data,level);  
        InOrderTraverse(T->rchild,level+1);  /*�������T��������*/  
    }  
}  
//����  
void PostOrderTraverse(BiTree T,int level)  
{  
    if(T)  
    {   /*�ݹ����������TΪ��*/  
        PostOrderTraverse(T->lchild,level+1);  /*�������T��������*/  
        PostOrderTraverse(T->rchild,level+1);  /*�������T��������*/  
        printf("node: %c, level: %d\n",T->data,level);  
    }  
}  
//ͳ�ƶ�����Ҷ�ӽڵ���  
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
//������������  
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
   BiTree T = NULL;  /*�ʼTָ���*/  
     
   CreatBiTree(&T);             //�������������Ȼ�������ͼ������ͼ�������봴��  
   printf("\n���������\n");  
   PreOrderTraverse(T,level);   //�������������ҵ�����D�ַ����λ�ڶ������еĲ���  
   printf("\n���������\n");  
   InOrderTraverse(T,level);    //�������������ҵ�����D�ַ����λ�ڶ������еĲ���  
   printf("\n���������\n");  
   PostOrderTraverse(T,level);  //�������������ҵ�����D�ַ����λ�ڶ������еĲ���  
      
   Node_num = CountLeaf(T);  
   Depth_num = TreeDepth(T);  
   printf("\nNode_num = %d, Depth_num = %d\n",Node_num,Depth_num);  
   getchar();
   return 0;
}  
