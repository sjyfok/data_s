#include <stdio.h>
#include <stdlib.h>

/*完全二叉搜索树的中序遍历就是从小到大有序的序列，因此排序得到中序遍历
完全二叉搜索树的右子树一定是完美二叉树，从而得到右子树的节点个数，也就得到了
根节点的位置，得到根节点后，就可以建立树，再做层次遍历。
*/
#define		MaxSize		1001

typedef int TElemType;

void SortInc(TElemType inser[], int N);
void DispSort(TElemType inser[], int N);
void  Build(int root);

int node[MaxSize];
int tree[MaxSize];
int pos;
int N;

int main(void)
{
	int i;

	//读入输入序列
	scanf("%d", &N);
	for (i = 0; i < N; i ++) {
		scanf("%d", &node[i]); 
	}
	//对输入数据进行排序
	SortInc(node, N);
	pos = 0;
	Build(1);

	for (i = 1; i < N; i ++)
		printf("%d ", tree[i]);
	printf("%d\n", tree[i]);

	return 0;
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

