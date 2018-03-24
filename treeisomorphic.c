#include <stdio.h>
#include <stdlib.h>

#define	MaxTree 10

typedef  char ElemType;
typedef  int	Tree;
#define	Null -1


struct TreeNode
{
	ElemType elem;

	Tree left;
	Tree right;
};
struct TreeNode T1[MaxTree], T2[MaxTree];

int BuiltTree(struct TreeNode T[]);
void PreOrderTraversal(struct TreeNode T[], Tree R);
int Isomorphic(Tree R1, Tree R2);

int main(void)
{
	Tree R1, R2;

	R1 = BuiltTree(T1);
	R2 = BuiltTree(T2);
//	PreOrderTraversal(T1, R1);
//	printf("\n");
//	PreOrderTraversal(T2, R2);
//	printf("\n");
	if (Isomorphic(R1, R2))
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}

int BuiltTree(struct TreeNode T[])
{
	int N, i;
	Tree R = 0;
	int Check[MaxTree];
	ElemType  cl, cr;
	scanf("%d", &N);
	if (N <= 0)
		return Null;
	//printf("%d\n", N);
	//确认根节点的位置

	for(i = 0; i < N; i ++)
		Check[i] = 0;

	for(i = 0; i < N; i ++)
	{
		ElemType c;

		scanf("%c ", &c);
		while(c == '\n' || c == ' ') scanf("%c", &c);
		T[i].elem = c;
		scanf("%c ", &c);
		while(c == '\n' || c == ' ') scanf("%c", &c);
		cl = c;
		scanf("%c ", &c);
		while(c == '\n' || c == ' ') scanf("%c", &c);
		cr = c;

//		while(scanf("%c %c %c\n", &T[i].elem,&cl,&cr);
		//printf("%c %c %c\n", T[i].elem, cl, cr);
		if (cl != '-') {
			T[i].left = cl-0x30;
			Check[T[i].left] = 1;
		}
		else T[i].left = Null;
		
		if (cr != '-') {
			T[i].right = cr-0x30;
			Check[T[i].right] = 1;
		}
		else T[i].right = Null; 
	}

	for(i = 0; i < N; i ++)
	{
		if (Check[i] == 0)
			R = i;
	}
	/*for (i = 0; i < N; i ++)
	{
		printf("%c %d %d\n", T[i].elem, T[i].left, T[i].right);
	}*/
	return R;
}

//先序遍历树
void PreOrderTraversal(struct TreeNode T[], Tree R)
{
	//printf("R= %d", R);
	if (R != Null)
	{
		printf("%c", T[R].elem);
		PreOrderTraversal(T, T[R].left);
		PreOrderTraversal(T, T[R].right);
	}
}

int Isomorphic(Tree R1, Tree R2)
{
	if ((R1 == Null) && (R2 == Null))
		return 1;
	if (((R1 == Null)&&(R2!= Null)) || ((R1 != Null)&&(R2 == Null)))
		return 0;
	if ((T1[R1].left == Null) && (T2[R2].left == Null) && (T1[R1].right = Null) &&
		(T2[R2].right == Null) && (T1[R1].elem != T2[R2].elem))
		return 0;
	if ((T1[R1].left == Null) && (T2[R2].left == Null))
		return Isomorphic(T1[R1].right, T2[R2].right);
	if (((T1[R1].left != Null)&&(T2[R2].left != Null)) &&
		((T1[T1[R1].left].elem) == (T2[T2[R2].left].elem)))
			return (Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right));
	else
		return (Isomorphic(T1[R1].left, T2[R2].right) && Isomorphic(T1[R1].right, T2[R2].left));
}
