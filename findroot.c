#include <stdio.h>
#include <stdlib.h>

#define		MaxSize		20

typedef int TElemType;
typedef struct TreeNode *PAVLTree;
struct TreeNode
{
	TElemType data;

	PAVLTree left;
	PAVLTree right;
	int bf;
};


PAVLTree  BuiltAVLTree(TElemType inser[], int N);
void PreOrderTraversal(PAVLTree  T);
void InsertAVL(PAVLTree *T, TElemType e);

int main(void)
{
	int N, i;
	PAVLTree T;
	TElemType inser[MaxSize];

	scanf("%d", &N);
	for (i = 0; i < N; i ++) {
		scanf("%d", &inser[i]); 
	}
	T = BuiltAVLTree(inser, N);
	PreOrderTraversal(T);
//	if (T)
//		printf("%d\n", T->data);
	return 0;
}

PAVLTree BuiltAVLTree(TElemType inser[], int N)
{
	//输入
	PAVLTree T = NULL;
	int i, V;
	
	for (i = 0; i < N; i ++) {
		InsertAVL(&T, inser[i]);
	}

	/*scanf("%d", &V);
	for (i = 1; i < N; i ++)
	{
		scanf("%d", &V);
	} */
	return T;
}

void InsertAVL(PAVLTree *T, TElemType e)
{

	if (!(*T)) {
		(*T) = (PAVLTree)malloc(sizeof(struct TreeNode));
		(*T)->left = (*T)->right = NULL;
		(*T)->data = e;
		(*T)->bf = 0;
	}
	else {
		if (e < (*T)->data) {
			InsertAVL(&((*T)->left), e);
		}
		else {
			InsertAVL(&((*T)->right), e);
		}
	}
}

//先序遍历树
void PreOrderTraversal(PAVLTree  T)
{
	if (T != NULL)
	{
		PreOrderTraversal(T->left);
		PreOrderTraversal(T->right);
		printf("%d ", T->data);
	}
}
/*
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
