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
