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
//���ܣ�	������̴�ӡ
//������	int* a ������ʼ��ַ��
//			int n;�����ܳ��ȣ�
//			int i ���������
//����ֵ��	��С�����±�
/*==================================================*/
void print(int* a,int n, int i)
{
	cout<<"��"<<i+1<<"������";
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
