#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MaxTree 30

typedef  int 	TElemType;
//typedef  Tree QElemType;
#define	Null -1

typedef struct TreeNode* PTree;
typedef PTree ElemType;

//辅助结构栈
struct Stack {
	ElemType *pBase;
	int i_sp;
	int cap;
};

typedef struct Stack*  PStack;

PStack  InitStack(int size);
void StackDestroy(PStack pstk);
int StackFull(PStack pstk);
int StackEmpty(PStack pstk);
int StackPush(PStack pstk, ElemType *elem);
int StackPop(PStack pstk, ElemType *elem);
int StackView(PStack pstk, ElemType *elem);
void StackDisp(PStack pstk);

struct ArrayNode
{
	int node;
	char inputStr[6];
};

struct TreeNode
{
	TElemType elem;

	PTree left;
	PTree right;
};


PTree  BuiltTree(void);
//void PreOrderTraversal(struct TreeNode T[], Tree R);
//int  LevelOrderTraversal(struct TreeNode T[], Tree R, int trav[]);
void LastOrderTraversal(PTree T);

TElemType array[MaxTree];
int g_idx = 0;

int main(void)
{
	int   i;
	PTree Tree;

	Tree = BuiltTree();
	LastOrderTraversal(Tree);
	for (i = 0; i < g_idx-1; i ++)
		printf("%d ", array[i]);
	printf("%d\n", array[i]);
	return 0;
}

PTree BuiltTree(void)
{
	//输入
	struct ArrayNode input[MaxTree+MaxTree];
	PStack pstk;
	PTree  T=NULL, pMid;
	int Dir = 0; //表示入栈
	int N, i;

	scanf("%d\n", &N);
	for (i = 0; i < 2*N; i ++)
	{
//		fgets(input[i], 8, stdin);
		scanf("%s", input[i].inputStr);
		//gets(input[i].inputStr);
		if (!strncmp("Push", input[i].inputStr, 4))
			scanf("%d\n", &input[i].node);
		else
			input[i].node = Null;
	}

	//printf("%d\n", N);
	pstk = InitStack(N);
	for (i = 0; i < 2*N; i ++)
	{
		if (!strncmp("Push", input[i].inputStr, 4))
		{
			PTree Tmp = (PTree)malloc(sizeof(struct TreeNode));
			Tmp->elem = input[i].node;
			Tmp->left = NULL;
			Tmp->right = NULL;
			if (T == NULL)
			{
				T = Tmp;
				//Dir = 0;
			}
			else
			{
				StackPop(pstk, &pMid);
				if (Dir == 0)
				{
					pMid->left = Tmp;
				}
				else
				{
					pMid->right = Tmp;					
				}
				StackPush(pstk, &pMid);
			}
			StackPush(pstk, &Tmp);
			Dir = 0;
		}
		else   //pop
		{
			if (Dir == 0)
			{
				Dir = 1;
			}
			else
			{
				StackPop(pstk, &pMid);
			}
		}
//		printf("%s %d\n", input[i].inputStr, input[i].node);
	}

	return T;//R;
}

//后序遍历树
//int LastOrderTraversal(PTree T, TElemType trav[])
void LastOrderTraversal(PTree T)
{
	//printf("R= %d", R);
	if (T != NULL)
	{
		//printf("lll");
		LastOrderTraversal(T->left);
		LastOrderTraversal(T->right);
		//printf("%d", T->elem);
		array[g_idx ++] = T->elem;
	}
}

//栈
PStack  InitStack(int size)
{
	PStack pStk = (PStack)malloc(sizeof(struct Stack));
	pStk->pBase = (ElemType*)malloc(sizeof(ElemType)*size);
	pStk->i_sp = 0;
	pStk->cap = size;
	return pStk;
}

void StackDestroy(PStack pstk)
{
	free(pstk->pBase);
	free(pstk);
}

int StackFull(PStack pstk)
{
	if (pstk->i_sp >= pstk->cap)
		return 1;
	return 0;
}

int StackEmpty(PStack pstk)
{
	if (pstk->i_sp == 0)
		return 1;
	return 0;
}

int  StackPush(PStack pstk, ElemType *elem)
{
	if (StackFull(pstk))
		return 0;
	pstk->pBase[pstk->i_sp ++] = *elem;
	return 1;
}

int StackPop(PStack pstk, ElemType *elem)
{
	if (StackEmpty(pstk))
		return 0;
	*elem = pstk->pBase[--pstk->i_sp];
	return 1;
}

int StackView(PStack pstk, ElemType *elem)
{
	if (StackEmpty(pstk))
		return 0;
	*elem = pstk->pBase[pstk->i_sp-1];
	return 1;
}

void StackDisp(PStack pstk)
{
	int i = 0;
	printf("Stack: ");
	while (i < pstk->i_sp) {
	//	printf("%d ", pstk->pBase[i]);
		i ++;
	}
	printf("\n");
}

