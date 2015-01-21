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
下面结合例子来演示一下“右左法则”的使用。 
int * (* (*fp1) (int) ) [10];
阅读步骤： 
1. 从变量名开始——fp1 
2. 往右看，什么也没有，碰到了)，因此往左看，碰到一个*——一个指针 
3. 跳出括号，碰到了(int)——一个带一个int参数的函数 
4. 向左看，发现一个*——（函数）返回一个指针 
5. 跳出括号，向右看，碰到[10]——一个10元素的数组 
6. 向左看，发现一个*——指针 
7. 向左看，发现int——int类型 

声明了一个指针，指向参数为int,返回值为指针的函数。
函数的返回值是一个数组，数组内的元素是整型指针。

int *( *( *arr[5])())();

阅读步骤： 

1. 从变量名开始——arr 
2. 往右看，发现是一个数组——一个5元素的数组 
3. 向左看，发现一个*——指针 
4. 跳出括号，向右看，发现()——不带参数的函数 
5. 向左看，碰到*——（函数）返回一个指针 
6. 跳出括号，向右发现()——不带参数的函数 
7. 向左，发现*——（函数）返回一个指针 
8. 继续向左，发现int——int类型 


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