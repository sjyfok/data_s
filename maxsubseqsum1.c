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
	printf("%d \n", sum);

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

