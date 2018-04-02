#include <stdio.h>
#include <stdlib.h>

#define		MaxSize		1001

typedef int TElemType;

void SortInc(TElemType inser[], int N);
void DispSort(TElemType inser[], int N);
void  Build(int root);
int cmp(const void *a, const void *b);

int node[MaxSize];
int tree[MaxSize];
int pos;
int N;

int main(void)
{
	int i;

	/////////////////////////////////
	//读取测试数据
/*	FILE *fp = fopen("test.file", "r");
	fscanf(fp, "%d", &N);
//	printf("N= %d\n", N);
	for (i = 0; i < N; i ++)
		fscanf(fp, "%d", &node[i]);  */
	/////////////////////////////////
		
	//读入输入序列
	scanf("%d", &N);
	for (i = 0; i < N; i ++) {
		scanf("%d", &node[i]); 
	}
	//对输入数据进行排序
	qsort(node, N, sizeof(int), cmp);
	//SortInc(node, N);
	pos = 0;
	Build(1);

	for (i = 1; i < N; i ++)
		printf("%d ", tree[i]);
	printf("%d\n", tree[i]);

	return 0;
}

int cmp(const void *a, const void *b)
{
	int *pa = (int*)a;
	int *pb = (int*)b;
	return *pa-*pb;
}

void  Build(int root)
{
	int lson, rson;

	if (root > N)
		return ;
	
	lson = root<<1;
	rson = (root<<1)+1;
	Build(lson);
	tree[root] = node[pos ++];
	Build(rson);
}

void SortInc(TElemType inser[], int N)
{
	int i, j;
	TElemType tmp;

	for (i = 0; i < N; i ++)
	{
		tmp = inser[i];
		for (j = i+1; j < N; j ++)
		{
			if (tmp > inser[j])
			{
				tmp = inser[j];
				inser[j] = inser[i];
			}
		}
		inser[i] = tmp;
	}
}

