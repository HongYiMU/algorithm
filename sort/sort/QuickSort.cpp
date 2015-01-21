#include <iostream>

using namespace std;

extern void print(int*a, int n, int i);
extern void swap(int* a, int *b);



/*==================================================
//功能：	根据基准值将数组划分成两部分	
//描述：	将小于基准值的数依次从左开始放置，
//			将大于基准值的数依次从右开始放。
//			
//参数：	int* a 数组起始地址；
//			int low;数组起始位置
//			int high数组结束位置
//返回值：	新的基准值的位置
/*==================================================*/
int patition(int* a, int low, int high)
{
	int n= high-low+1;

	int privotKey = a[low];
	while(low < high){
		while(low < high && privotKey <= a[high]) high--;
		if(low == high)
		{
			break;
		}
		swap(&a[low],&a[high]);
		while(low < high && privotKey >= a[low]) low++;
		if(low == high)
		{
			break;
		}
		swap(&a[low], &a[high]);
	}
	//a[low] = privotKey;
	//print(a,10,0);
	return low;
}


/*==================================================
//功能：	快速排序	
//描述：	1、选取基准值，将数组分为两部分：
//					小于基准值的和大于等于基准值的
//			2、用递归的方法分别对这两部分进行排序。
//参数：	int* a 数组起始地址；
//			int n;数组总长度；
//返回值：
/*==================================================*/
void QuickSort(int* a, int low, int high)
{
	
	if(low < high)
	{	
		print(a,10,low);
		int privotLoc = patition(a,low,high);
		QuickSort(a,low,privotLoc-1);
		QuickSort(a,privotLoc+1,high);
	}
}


