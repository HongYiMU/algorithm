#include <iostream>

using namespace std;

extern void print(int*a, int n, int i);
extern void swap(int* a, int *b);



/*==================================================
//���ܣ�	���ݻ�׼ֵ�����黮�ֳ�������	
//������	��С�ڻ�׼ֵ�������δ���ʼ���ã�
//			�����ڻ�׼ֵ�������δ��ҿ�ʼ�š�
//			
//������	int* a ������ʼ��ַ��
//			int low;������ʼλ��
//			int high�������λ��
//����ֵ��	�µĻ�׼ֵ��λ��
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
//���ܣ�	��������	
//������	1��ѡȡ��׼ֵ���������Ϊ�����֣�
//					С�ڻ�׼ֵ�ĺʹ��ڵ��ڻ�׼ֵ��
//			2���õݹ�ķ����ֱ���������ֽ�������
//������	int* a ������ʼ��ַ��
//			int n;�����ܳ��ȣ�
//����ֵ��
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


