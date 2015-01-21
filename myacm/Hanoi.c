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
	将a 位置盘子移动到c位置，b位置作为中转站。
	在第二次移动时，
*/
static void move(int n,char a,char b, char c)
{
	if(n>=1)
	{
		move(n-1,a,c,b);
		printf("第%d次==%c->%c\n",n,a,c);
		move(n-1,b,a,c);
	}
}
