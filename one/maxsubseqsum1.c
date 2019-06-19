/*
给定K个整数组成的序列{ N​1​​, N​2​​, ..., N​K​​ }，“连续子列”被定义为{ N​i​​, N​i+1​​, ..., N​j​​ }，其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。

本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：

    数据1：与样例等价，测试基本正确性；
    数据2：102个随机整数；
    数据3：103个随机整数；
    数据4：104个随机整数；
    数据5：105个随机整数；

输入格式:

输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。
输出格式:

在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。
输入样例:

6
-2 11 -4 13 -5 -2

输出样例:

20
*/
#include <stdio.h>

int maxsubseq2(int list[], int N);

int main(void)
{
	int A[100000], len = 0;
	int i, sum, start, end;

	scanf("%d", &len);

	for(i = 0; i < len; i ++)
	{
		scanf("%d", &A[i]); 
	}

	sum = maxsubseq2(A, len );
	//printf("%d %d %d\n", sum, start, end);
	printf("%d\n", sum);

	return 0;
}

int maxsubseq2(int list[], int N)
{
	int thisSum, maxSum;
	int i, j;

	maxSum = 0;
	for (i = 0; i < N; i ++) {
		thisSum = 0;
		for (j = i; j < N; j ++) {
			thisSum += list[j];
			if (thisSum > maxSum) {
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

int maxsubseq3(int list[], int N, int *s, int *e)
{
	int thisSum, maxSum;

	int i, tmp, is, ie;
	thisSum = maxSum = 0;
	*s = list[0];
	*e = list[N-1];
	is = 0;
	ie = N-1;

	tmp = list[0];

	for (i = 0; i < N; i ++)
	{
		thisSum  += list[i];
		if (thisSum > maxSum)
		{
			maxSum = thisSum;
			*e = list[i];			
		} else if (thisSum < 0)
		{
			thisSum = 0;
			*s = tmp;
			if (i+1 < N) {
	//			printf("t %d ", tmp);
				tmp = list[i+1];
				}
		}
		else  //thisSum == maxSum
		{
			
		}
	}
//	*s = tmp;
	return maxSum;
}

