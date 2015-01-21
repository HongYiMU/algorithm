/**********************************************
//Subscript : Sorting It All Out
//Description:
//An ascending sorted sequence of distinct values is one in which
//some form of a less-than operator is used to order the elements
//from smallest to largest. 
//For example, the sorted sequence A, B, C, D implies that A < B, B < C and C < D. 

//�������е������ص���������ֵ��С˳���ʽ����С�ڲ�������Ԫ�ش�С����������ġ�
//����:һ������ŵ�����A,B,C,D��ζ��A<B,B<C,C<D��
//in this problem, we will give you a set of relations of the form A < B and ask you to 
//determine whether a sorted order has been specified or not. 
//����������У����ǻ����һ����A<B�Ĺ�ϵ��ʽ�����������������ʽ�Ƿ���ָ���ġ�

//Input
//Input consists of multiple problem instances. 
//�����ɶ��ʵ��������ɡ�
//Each instance starts with a line containing two positive integers n and m. 
//ÿ��ʵ���ɰ���������������n��m��ɡ�
//the first value indicated the number of objects to sort, where 2 <= n <= 26. 
//��һ��ֵnԤʾҪ������Ķ���ĸ�����(26����ĸ) n �ķ�Χ��2<=n<=26.
//The objects to be sorted will be the first n characters of the uppercase alphabet. 
//ǰn��д��ĸ��Ҫ������Ķ���
//The second value m indicates the number of relations of the form A < B which will be given in this problem instance. 
//�ڶ���ֵmָ�����ڸ�����ʵ���еĹ�ϵ��ĸ��������м�����С��ϵ��
//Next will be m lines, each containing one such relation consisting of three characters: 
//��������m�����룬ÿһ�ж������������ָ�ʽ��ϵ�������ַ�
//an uppercase letter, the character "<" and a second uppercase letter. 
//һ����д��ĸ��һ��<�ţ�����һ����д��ĸ
//No letter will be outside the range of the first n letters of the alphabet. 
//��ĸ���ܳ�����д��ĸ�ķ�Χ
//Values of n = m = 0 indicate end of input.n ��m ��Ϊ��ʱ�����������

//Output
//For each problem instance, output consists of one line. 
//This line should be one of the following three: 
//ÿһ������ʵ���������������ʾ��֮һ��

//Sorted sequence determined after xxx relations: yyy...y. 
//Sorted sequence cannot be determined. 
//Inconsistency found after xxx relations. 

//where xxx is the number of relations processed at the time 
//either a sorted sequence is determined or an inconsistency is found, 
xxx�����м����ַ��ķ�Χ��yyy...y�����⼸���ַ����������С�
//whichever comes first, and yyy...y is the sorted, ascending sequence. 
//��������

4 6
A<B
A<C
B<C
C<D
B<D
A<B

3 2
A<B
B<A
26 1
A<Z
0 0

�������

Sorted sequence determined after 4 relations: ABCD.
Inconsistency found after 2 relations.
Sorted sequence cannot be determined.

Source

East Central North America 2001
************************************************/
#include "common.h"

extern void SortingItAllOut();
char** InputLine();

void SortingItAllOut()
{
	//char **Inputs = InputLine();
}

char** InputLine()
{
	return NULL;
}
