#include <iostream>

using namespace std;
//extern void BubbleSort(int* a, int n);
extern void print(int* a,int n, int i);
extern void swap(int* a, int *b);

/*==================================================
//���ܣ�	ð������	
//			����ѡȡ���������βλ��������
//������	int* a ������ʼ��ַ��
//			int n;�����ܳ��ȣ�
//����ֵ��
/*==================================================*/
void BubbleSort1(int* a, int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1; j++)
		{
			if(a[j] > a[j+1])
			{
				swap(&a[j], &a[j+1]);
			}
		}
		print(a,n,i);
	}
}


/*==================================================
//���ܣ�	ð������	
//			����ѡȡ���������βλ��������
//������	int* a ������ʼ��ַ��
//			int n;�����ܳ��ȣ�
//����ֵ��
/*==================================================*/
void BubbleSort2(int* a, int n)
{
	int k = 1;
	for(int i=0; i<n && k==1; i++)
	{
		k=0;
		for(int j=0; j<n-i-1; j++)
		{
			if(a[j] > a[j+1])
			{
				k=1;
				swap(&a[j], &a[j+1]);
			}
		}
		print(a,n,i);
	}
}


/*==================================================
//���ܣ�	ð������	
//			����ѡȡ���������βλ��������
//������	int* a ������ʼ��ַ��
//			int n;�����ܳ��ȣ�
//����ֵ��
/*==================================================*/
void BubbleSort(int* a, int n)
{
	int j = n-1;
	while(j>0)
	{
		int pos = 0;
		for(int i=0; i<j; i++)
		{
			if(a[i] > a[i+1])
			{
				pos = i;
				swap(&a[i], &a[i+1]);
			}
		}
		j = pos;
		print(a,n,j);
	}
}

/*==================================================
//���ܣ�	ð������	
//			����ѡȡ���������βλ��������
//������	int* a ������ʼ��ַ��
//			int n;�����ܳ��ȣ�
//����ֵ��
/*==================================================*/
void BubbleSort4(int* a, int n)
{
	int high = n-1;
	int low = 0;
	while(high>low)
	{
		int iPosHigh = 0;
		int iPosLow = 0;
		for(int i=low; i<high; i++)
		{
			if(a[i] > a[i+1])
			{
				iPosHigh = i;
				swap(&a[i], &a[i+1]);
			}
		}
		high = iPosHigh;
		
		for(int i=high;i>low; i--)
		{
			if(a[i] < a[i-1])
			{
				iPosLow = i;
				swap(&a[i], &a[i-1]);
			}
		}
		low = iPosLow;
		print(a,n,high);
	}
}





