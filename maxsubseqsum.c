#include <stdio.h>

int maxsubseq3(int list[], int N, int *s, int *e);

int main(void)
{
	int A[100000], len = 0;
	int i, sum, start, end;

	scanf("%d", &len);

	for(i = 0; i < len; i ++)
	{
		scanf("%d", &A[i]); 
	}

	sum = maxsubseq3(A, len, &start, &end);
	printf("%d %d %d\n", sum, start, end);
	//printf("%d\n", sum);

	return 0;
}

int maxsubseq3(int list[], int N, int *s, int *e)
{
	int thisSum, maxSum;

	int i, tmp, is, ie;
	thisSum = maxSum = 0;
	*s = 0; //list[0];
	tmp = 0;
	*e = N-1;//list[N-1];

	for (i = 0; i < N; i ++)
	{
		thisSum  += list[i];
		if (thisSum > maxSum)
		{
			maxSum = thisSum;
			*e = i;//list[i];			
			*s = tmp;
		} else if (thisSum < 0)
		{
			thisSum = 0;
			tmp = i+1;
		}
		else  //thisSum == maxSum
		{
			
		}
	}
	return maxSum;
}

