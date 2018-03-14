#include <stdio.h>
#include <stdlib.h>

#define	MaxTree 10


struct TreeNode
{
	char elem;
	int left;
	int right;
};
struct TreeNode T1[MaxTree], T2[MaxTree];

int BuiltTree(struct TreeNode T[])
{
	int N, i, R = 0;
	int *ptrCheck;
	char cl, cr;
	scanf("%d\n", &N);
	if (N <= 0)
		return 0;
	ptrCheck = (int*)malloc(sizeof(int)*N);
	for(i = 0; i < N; i ++)
		ptrCheck[i] = 0;

	for(i = 0; i < N-1; i ++)
	{
		scanf("%c %c %c\n", &(T[i].elem), &cl, &cr);
		T[i].left = cl;
		T[i].right = cr;
		if (cl != '-') {
			ptrCheck[T[i].left] = 1;
			T[i].left = -1;
		}
		else	if (cr != '-') {
			ptrCheck[T[i].right] = 1;
			T[i].right = -1;
		}
	}
	for(i = 0; i < N; i ++)
	{
		if (ptrCheck[i] == 0)
			R = i;
	}
	return R;
}

void PrintTree(struct TreeNode T[], int N)
{
	int i;
	
	printf("\n");
	for(i = 0; i < N; i ++)
	{
		printf("%c %d %d\n", T[i].elem, T[i].left, T[i].right);
	}
}

int main(void)
{
	int R1, R2;
	
	R1 = BuiltTree(T1);
	PrintTree(T1, 8);
/*	R2 = BuiltTree(T2);

	if (Isomorphic(R1, R2))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
*/
	return 0;
}
