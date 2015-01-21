#include "common.h"
void HeapSort(int* a, int n);
void BuildMaxHeap(int* a,int n);
void MaxHeapify(int* a,int n,int i);

#define PARENT(i) ((i)>>1)
#define LEFT(i)	((i)<<1)
#define RIGHT(i) ((i)<<1)+1

/************************************************************************/
//堆排序过程
//			1.将数组组建成最大堆。（堆顶为最大值）
//			2.分两部分：
//				(1)将最大值与堆底的元素交换（将最大值放到数组的最后）
//				(2)对除去最后一个最大值的堆调整成新的最大堆。
/************************************************************************/
void HeapSort(int* a, int n)
{
	int i;
	int heapSize = n;
	BuildMaxHeap(a,n);
	Debug(a,n,0);

	for(i=n-1; i>0; i--)
	{
		Swap(&a[0],&a[i]);
		heapSize--;
		MaxHeapify(a,heapSize,1);
	}
}
/************************************************************************/
//建立最大堆
//从最后一个结点开始，依次调整每个结点，使之成为最大堆
/************************************************************************/
void BuildMaxHeap(int* a,int n)
{
	int i;
	for(i=n/2; i>0;i--)
	{
		MaxHeapify(a,n,i);
	}
}
/************************************************************************/
//使以i为根的子堆成为最大堆                                                                     
/************************************************************************/
void MaxHeapify(int* a,int n,int i)
{
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;
	Debug(a,n,0);
	if(l<=n && a[i-1]<a[l-1])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if(r<= n && a[r-1] > a[largest-1])
	{
		largest = r;
	}
	if(i != largest)
	{
		Swap(&a[i-1],&a[largest-1]);
		MaxHeapify(a,n,largest);
	}
}

/*
优先级队列
是一种用来维护由一组元素构成的集合S的数据结构，这一组元素中的每一个都有一个关键字key。
一个最大优先级队列支持以下操作：
INSERT(S,x):把元素x插入集合S。
MAXIMUM(S):返回S中具有最大关键字的元素。
EXTRACT-MAX(S):去掉并返回S中的具有最大关键字的元素。
INCREASE-KEY(S,x,k):将元素x的关键字的值增加到k,这里k值不能小于x的原关键字的值。

最大优先级队列的一个应用是在一台分时计算机上进行作业调度。
这种队列队要执行的各作业及他们之间的相对优先关系加以记录。
当一个作业做完或被中断时，用EXTRACT-MAX操作从所有等待的作业中，选择出具有最高优先级的作业。
在任何时候，一个新作业都可以用INSERT加入到队列中去。

*/