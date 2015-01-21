
#include "common.h"

static void InsertionSort(int* a,int n);
static void MergeSort(int* a,int p,int r);
static void Merge(int* a,int p,int q,int r);



static void InsertionSort(int* a,int n)
{
	int j;
	for(j=1;j<n;j++)
	{
		int key = a[j];
		int i = j-1;
		while(i>=0 && a[i]>key)
		{
			a[i+1] = a[i];
			i--;
		}
		a[i+1] = key;
	}
}

static void MergeSort(int* a,int p,int r)
{
	int q=0;
	if(r-p>=7)
	{
		q = (r+p)/2;
		MergeSort(a,p,q);
		MergeSort(a,q+1,r);
		Merge(a,p,q,r);
	}
	else
	{
		InsertionSort(a+q,r-q+1);
	}
	Debug(a,r-p+1,p);

}


static void Merge(int* a,int p,int q,int r)
{
	int i=0,j=0;
	int len = r-p+1;
	int first1 = p,
		last1 = q;
	int first2 = q+1,
		last2 = r;
	int *t = (int*)malloc(len*sizeof(int));
	if( t== NULL || len == 0)
	{
		return;
	}
	while(first1 <= last1 && first2 <= last2)
	{
		if(a[first1] < a[first2])
		{
			t[i] = a[first1];
			first1++;
			i++;
		}
		else
		{
			t[i] = a[first2];
			first2 ++;
			i++;
		}
	}
	while(first1 <= last1)
	{
		t[i] = a[first1];
		first1++;
		i++;
	}
	while(first2 <= last2)
	{
		t[i] = a[first2];
		first2++;
		i++;
	}
	for(i=p,j=0; i<=r; j++,i++)
	{
		a[i] = t[j];
	}
	free(t);
}

