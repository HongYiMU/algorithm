/**********************************************
//Subscript : Sorting It All Out
//Description:
//An ascending sorted sequence of distinct values is one in which
//some form of a less-than operator is used to order the elements
//from smallest to largest. 
//For example, the sorted sequence A, B, C, D implies that A < B, B < C and C < D. 

//升序排列的明显特点是他的数值大小顺序格式是用小于操作来将元素从小到大来排序的。
//例如:一个排序号的数列A,B,C,D意味着A<B,B<C,C<D。
//in this problem, we will give you a set of relations of the form A < B and ask you to 
//determine whether a sorted order has been specified or not. 
//在这个问题中，我们会给你一组如A<B的关系格式。请你来决定这组格式是否是指定的。

//Input
//Input consists of multiple problem instances. 
//输入由多个实例问题组成。
//Each instance starts with a line containing two positive integers n and m. 
//每个实例由包含两个正整数的n和m组成。
//the first value indicated the number of objects to sort, where 2 <= n <= 26. 
//第一个值n预示要被排序的对象的个数，(26个字母) n 的范围：2<=n<=26.
//The objects to be sorted will be the first n characters of the uppercase alphabet. 
//前n大写字母是要被排序的对象
//The second value m indicates the number of relations of the form A < B which will be given in this problem instance. 
//第二个值m指的是在给定的实例中的关系组的个数。（有几个大小关系）
//Next will be m lines, each containing one such relation consisting of three characters: 
//接下类是m行输入，每一行都包含代表这种格式关系的三个字符
//an uppercase letter, the character "<" and a second uppercase letter. 
//一个大写字母，一个<号，和另一个大写字母
//No letter will be outside the range of the first n letters of the alphabet. 
//字母不能超出大写字母的范围
//Values of n = m = 0 indicate end of input.n 和m 都为零时代表输入结束

//Output
//For each problem instance, output consists of one line. 
//This line should be one of the following three: 
//每一个问题实例都输出以下三行示例之一。

//Sorted sequence determined after xxx relations: yyy...y. 
//Sorted sequence cannot be determined. 
//Inconsistency found after xxx relations. 

//where xxx is the number of relations processed at the time 
//either a sorted sequence is determined or an inconsistency is found, 
xxx代表有几个字符的范围。yyy...y代表这几个字符的升序排列。
//whichever comes first, and yyy...y is the sorted, ascending sequence. 
//输入样例

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

输出样例

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
