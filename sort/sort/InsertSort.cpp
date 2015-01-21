#include <iostream>

using namespace std;

//extern void InsertSort(int* a, int n);

//extern void ShellSort(int* a, int n);


extern void print(int* a,int n, int i);

/*=============================================
//第1趟排序1 2 9 3 0 8 4 7 3 6
//第2趟排序1 2 9 3 0 8 4 7 3 6
//第3趟排序1 2 3 9 0 8 4 7 3 6
//第4趟排序0 1 2 3 9 8 4 7 3 6
//第5趟排序0 1 2 3 8 9 4 7 3 6
//第6趟排序0 1 2 3 4 8 9 7 3 6
//第7趟排序0 1 2 3 4 7 8 9 3 6
//第8趟排序0 1 2 3 3 4 7 8 9 6
//第9趟排序0 1 2 3 3 4 6 7 8 9
/*============================================*/

/*==================================================
//功能：	插入排序
//描述：	从起始位置开始将较大数依次后移，较小数插入到较大数前面
//参数：	int* a 数组起始地址；
//			int n;数组总长度；
//返回值：
/*==================================================*/
void InsertSort(int* a,int n)
{
	for(int i=1; i<n; i++)
	{
		int filter = a[i];
		int j = i-1;
		while(filter < a[j] && j>=0)
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = filter;
		print(a,n,i-1);
	}
}


/*==================================================
//功能：	插入排序
//描述：	从起始位置开始将较大数依次后移，较小数插入到较大数前面
//参数：	int* a 数组起始地址；
//			int d 跨度/增量；
//			int n;数组总长度；
//返回值：
/*==================================================*/
void ShellInsertSort(int* a,int d,int n)
{
	for(int i=d; i<n; i++)
	{
		
		int temp = a[i];
		int j = i-d;
		while(a[j] > temp  && j>=0)
		{
			a[j+d] = a[j];
			j-=d;
		}
		if(j != i-d)
			a[j+d] = temp;
		///print(a,n,i-d);
	}
}


/*==================================================
//功能：	希尔排序
//描述：	另一种插入排序。
//			将数组分成k组，对每一组进行插入排序
//参数：	int* a 数组起始地址；
//			int d 跨度/增量；
//			int n;数组总长度；
//返回值：
/*==================================================*/

void ShellSort(int* a, int n)
{
	int d = n/2;
	while(d>=1)
	{
		ShellInsertSort(a,d,n);
		d /=2;
		print(a,n,d);
	}

}


