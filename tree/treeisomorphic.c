/*
给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。


图1


图2
现给定两棵树，请你判断它们是否是同构的。

输入格式:

输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。
输出格式:

如果两棵树是同构的，输出“Yes”，否则输出“No”。
输入样例1（对应图1）：

8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -

输出样例1:

Yes

输入样例2（对应图2）：

8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4

输出样例2:

No


*/
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
