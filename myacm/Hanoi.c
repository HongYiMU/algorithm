#include "common.h"

extern void Hanoi();

static void move(int n,char a,char b, char c);

void Hanoi()
{
	int n;
	printf("Input the number of disks:");
	scanf("%d",&n);
	move(n,'A','B','C');
}
/*
	��a λ�������ƶ���cλ�ã�bλ����Ϊ��תվ��
	�ڵڶ����ƶ�ʱ��
*/
static void move(int n,char a,char b, char c)
{
	if(n>=1)
	{
		move(n-1,a,c,b);
		printf("��%d��==%c->%c\n",n,a,c);
		move(n-1,b,a,c);
	}
}
