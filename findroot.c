#include <stdio.h>
#include <stdlib.h>

#define		MaxSize		20

#define		EH	 0
#define		LH	 1
#define		RH	-1


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
int InsertAVL(PAVLTree *T, TElemType e, int *taller);

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

int InsertAVL(PAVLTree *T, TElemType e, int *taller)
{

	if (!(*T)) {
		(*T) = (PAVLTree)malloc(sizeof(struct TreeNode));
		(*T)->left = (*T)->right = NULL;
		(*T)->data = e;
		(*T)->bf = EH;
		*taller = 1;
		return 1;
	}
	else {
		if (e < (*T)->data) {
			if (InsertAVL(&((*T)->left), e, taller)) {
				if (*taller) {
					switch ((*T)->bf) {
					case LH:
						LeftBalance(T);
						*taller = 0;
						break;
					case EH:
						(*T)->bf = LH;
						*taller = 1;
						break;
					case RH:
						(*T)->bf = EH;
						*taller = 0;
						break;
					default:
						return 0;
					}
				}
			}
		}
		else {
			if (InsertAVL(&((*T)->right), e, taller)) {
				if (*taller) {
					switch ((*T)->bf) {
					case LH:
						(*T)->bf = EH;
						*taller = 0;
						break;
					case EH:
						(*T)->bf = RH;
						*taller = 1;
						break;
					case RH:
						RightBalance(*T);
						*taller = 0;
						break;
					}
				}
			}
		}
	}

	return 0;
}

void LeftBalance(PAVLTree *T)
{
	PAVLTree *lc;
	lc = (*T)->left;
	switch(lc->bf) {
	case LH:
		(*T)->bf = lc->bf = EH;
		R_Rotate(*T);
		break;
	case RH:
		rd = lc->right;
		switch(rd->bf) {
		case LH:
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
