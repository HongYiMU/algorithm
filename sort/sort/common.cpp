#include <iostream>
using namespace std;

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
