#include "common.h"
void Debug(int* a,int n,int k){
	while(n--)
	{
		printf("%d ",a[k++]);
	}
	printf("\n");
}

void Swap(int* a, int* b)
{
	if(*a != *b)
	{
		*a = *a^*b;
		*b = *a^*b;
		*a = *a^*b;
	}
	
}