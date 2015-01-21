#include "common.h"
extern void Sort();
int Len;
void Sort()
{
	int a[]= {39,73,17,4,7,6,10,9,23,14,29,13,34,8,19,49,53,21,5,12,54,63,18,43,24,1,3};
	//int a[] = {4,1,3,2,16,9,10,14,8,7};
	//int a[] = {2,5,3,0,2,3,0,3};
	//b保存排序好后的结果
	//int* b = (int*)malloc(sizeof(a)/sizeof(int));
	//Len = sizeof(a)/sizeof(int);
	
	Debug(a,sizeof(a)/sizeof(int),0);
	//InsertionSort(a,sizeof(a)/sizeof(int));
	//MergeSort(a,0,sizeof(a)/sizeof(int)-1);
	//HeapSort(a,sizeof(a)/sizeof(int));
	//QuickSort(a,0,sizeof(a)/sizeof(int)-1);
	//CountingSort(a,b,5);
	//Debug(b,Len,0);
	
	Debug(a,sizeof(a)/sizeof(int),0);
}

