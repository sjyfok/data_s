/*
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。
输入格式:

输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。
输出格式:

对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。
输入样例:

4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0

输出样例:

Yes
No
No

鸣谢青岛大学周强老师补充测试数据！
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MaxSize		100
typedef int TElemType;
typedef struct TreeNode *PTree;
struct TreeNode
{
	TElemType v;

	PTree left;
	PTree right;
	int flag;
};


PTree Insert(PTree T, TElemType V);
PTree  BuiltTree(int N);
PTree NewNode(TElemType V);
int check(PTree T, int V);
int Judge(PTree T, int N);
void ResetT(PTree T);
void FreeTree(PTree T);

int main(void)
{
	int N, L, i;
	PTree T;
	int O[MaxSize];
	int cnt = 0;

	scanf("%d", &N);
	while (N) {
		scanf("%d", &L);
		T = BuiltTree(N);
		for (i = 0; i < L; i ++) {
			if (Judge(T, N))
				O[cnt ++] = 1;
				//printf("Yes\n");
			else
				//printf("No\n");
				O[cnt ++] = 0;
			ResetT(T);
		}
		FreeTree(T);
		scanf("%d", &N);
	}
	for (i = 0; i < cnt; i ++) {
		if (O[i] == 1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	
	return 0;
}

PTree BuiltTree(int N)
{
	//输入
	PTree T;
	int i, V;


	scanf("%d", &V);
	T = NewNode(V);
	for (i = 1; i < N; i ++)
	{
		scanf("%d", &V);
		T = Insert(T, V);
	}
	return T;
}

PTree Insert(PTree T, TElemType V)
{
	if (!T) 
		T = NewNode(V);
	else {
		if (V > T->v)
			T->right = Insert(T->right, V);
		else
			T->left = Insert(T->left, V);
	}
	return T;
}

PTree NewNode(TElemType V)
{
	PTree T = (PTree)malloc(sizeof(struct TreeNode));
	T->v = V;
	T->left = T->right = NULL;
	T->flag = 0;
	return T;
}

int check(PTree T, int V)
{
	if (T->flag) {
		if (V < T->v)
			return check(T->left, V);
		else if (V > T->v) 
			return check(T->right, V);
		else return 0;
	}
	else {
		if (V == T->v) {
			T->flag = 1;
			return 1;
		}
		else
			return 0;
	}
}

int Judge(PTree T, int N)
{
	int i, V, flag = 0;

	scanf("%d", &V);
	if (V != T->v) 
		flag = 1;
	else
		T->flag = 1;
	for (i = 1; i < N; i ++) {
		scanf("%d", &V);
		if ((!flag) && (!check(T, V))) flag = 1;
	}
	if (flag)
		return 0;
	else	
		return 1;
}

void ResetT(PTree T)
{
	if (T->left)
		ResetT(T->left);
	if (T->right)
		ResetT(T->right);
	T->flag = 0;
}

void FreeTree(PTree T)
{
	if (T->left)
		FreeTree(T->left);
	if (T->right)
		FreeTree(T->right);
	free(T);
}
//先序遍历树
/*void PreOrderTraversal(struct TreeNode T[], Tree R)
{
	//printf("R= %d", R);
	if (R != Null)
	{
		//printf("%c", T[R].elem);
		if (T[R].left == Null && T[R].right == Null)
			printf("%d", R);
		PreOrderTraversal(T, T[R].left);
		PreOrderTraversal(T, T[R].right);
	}
}

//层次遍历
int  LevelOrderTraversal(struct TreeNode T[], Tree R, int trav[])
{
	PQue que;
	Tree TN;
	int i = 0;
	que = QueInit(MaxTree);
	if (R != Null) {
		QueInput(que, R);
		while (!QueEmpty(que)) {
			QueOutput(que, &TN);
			if((T[TN].left == Null) && (T[TN].right == Null))
				trav[i ++] = TN;
				//printf("%d", TN);
			if (T[TN].left != Null)
				QueInput(que, T[TN].left);
			if (T[TN].right != Null)
				QueInput(que, T[TN].right);
		}
	}
	return i;	
}
*/
