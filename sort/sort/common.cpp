#include <iostream>
using namespace std;

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
