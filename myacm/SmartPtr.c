#include "common.h"


extern void SmartPtr();
static void* func1(void* arg);
static void* func2(void* arg);
static void* func3(void* arg);
typedef void* (*SmartFun)(void* arg);
static void transfer(SmartFun* fun);

void SmartPtr()
{
	int i;
	void* (*(SmartPointer[3]))(void*) ={func1,func2,func3};
	SmartFun FunArry[]={func1,func2,func3};
	SmartFun funPtr;

	for(i=0;i<3;i++)
	{
		SmartPointer[i](&i);
	}
	
	for(i=0;i<3;i++)
	{
		FunArry[i](&i);
	}

	funPtr=func1;
	funPtr(&funPtr);
}

static void* func1(void* arg)
{
	printf("%s--%x\n",__FUNCDNAME__,arg);
	return NULL;
}
static void* func2(void* arg)
{
	printf("%s--%x\n",__FUNCDNAME__,arg);
	return NULL;
}
static void* func3(void* arg)
{
	printf("%s--%x\n",__FUNCDNAME__,arg);
	return NULL;
}
/*
��������������ʾһ�¡������򡱵�ʹ�á� 
int * (* (*fp1) (int) ) [10];
�Ķ����裺 
1. �ӱ�������ʼ����fp1 
2. ���ҿ���ʲôҲû�У�������)��������󿴣�����һ��*����һ��ָ�� 
3. �������ţ�������(int)����һ����һ��int�����ĺ��� 
4. ���󿴣�����һ��*����������������һ��ָ�� 
5. �������ţ����ҿ�������[10]����һ��10Ԫ�ص����� 
6. ���󿴣�����һ��*����ָ�� 
7. ���󿴣�����int����int���� 

������һ��ָ�룬ָ�����Ϊint,����ֵΪָ��ĺ�����
�����ķ���ֵ��һ�����飬�����ڵ�Ԫ��������ָ�롣

int *( *( *arr[5])())();

�Ķ����裺 

1. �ӱ�������ʼ����arr 
2. ���ҿ���������һ�����顪��һ��5Ԫ�ص����� 
3. ���󿴣�����һ��*����ָ�� 
4. �������ţ����ҿ�������()�������������ĺ��� 
5. ���󿴣�����*����������������һ��ָ�� 
6. �������ţ����ҷ���()�������������ĺ��� 
7. ���󣬷���*����������������һ��ָ�� 
8. �������󣬷���int����int���� 


float ( * ( *b()) [] )();
// b is a function that returns a 
// pointer to an array of pointers 
// to functions returning floats. 
void * ( *c) ( char, int (*)());
// c is a pointer to a function that takes 
// two parameters: 
// a char and a pointer to a 
// function that takes no 
// parameters and returns 
// an int 
// and returns a pointer to void. 
void ** (*d) (int &, char **(*)(char *, char **));
// d is a pointer to a function that takes 
// two parameters: 
// a reference to an int and a pointer 
// to a function that takes two parameters: 
// a pointer to a char and a pointer 
// to a pointer to a char 
// and returns a pointer to a pointer 
// to a char 
// and returns a pointer to a pointer to void 
float ( * ( * e[10]) (int &) ) [5];
// e is an array of 10 pointers to 
// functions that take a single 
// reference to an int as an argument 
// and return pointers to 
// an array of 5 floats.


*/