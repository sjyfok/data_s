#include <stdio.h>

int maxsubseq3(int list[], int N, int *s, int *e);

int main(void)
{
	int A[10000], len = 0;
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

	int i, tmp;
	thisSum = maxSum = 0;
	*s = list[0];
	*e = list[N-1];
	tmp = 0;

	for (i = 0; i < N; i ++)
	{
		thisSum  += list[i];
		if (thisSum > maxSum)
		{
			maxSum = thisSum;
			*e = list[i];			
			while(list[tmp] == 0)
				tmp ++;
			*s = list[tmp];
		} else if (thisSum < 0)
		{
			thisSum = 0;
			tmp = i+1;
		}
		else  //thisSum == maxSum
		{
			
		}
	}
	if (*s == list[0] && *e == list[N-1])
	{
		for (i = 0; i < N; i ++) {
			if (list[i] >= 0) {
				*s = list[i];
				*e = list[i];
				break;
			}
		}
	}
	return maxSum;
}

