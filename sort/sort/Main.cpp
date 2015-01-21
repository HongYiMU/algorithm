#include <iostream>
#include "common.h"
using namespace std;

extern void QuickSort(int* a, int low, int high);
extern void ShellSort(int* a, int n);
extern void InsertSort(int* a, int n);
extern void SelectSort(int* a, int n);
extern void BubbleSort(int* a, int n);
extern void print(int* a,int n, int i);
extern void swap(int* a, int *b);

/*==================================================
//功能：	排序过程打印
//参数：	int* a 数组起始地址；
//			int n;数组总长度；
//			int i 排序的趟数
//返回值：	最小数的下标
/*==================================================*/
void print(int* a,int n, int i)
{
	cout<<"第"<<i+1<<"趟排序";
	for(int i=0; i<n; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void swap(int* a, int *b)
{
	*a = *a+*b;
	*b = *a-*b;
	*a = *a-*b;
}



int main(void)
{
	int a[] = {1,5,2,9,3,0,8,4,7,3,6};
	print(a,sizeof(a)/sizeof(int),-1);
	//ShellSort(a,sizeof(a)/sizeof(int));
	//QuickSort(a,0,sizeof(a)/sizeof(int)-1);
	BubbleSort(a,sizeof(a)/sizeof(int));
	print(a,sizeof(a)/sizeof(int),-1);
	system("pause");
	return 0;
}
