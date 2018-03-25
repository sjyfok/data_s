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

int main(void)
{
	int  len, i;
	PTree Tree;

	Tree = BuiltTree();
//	R2 = BuiltTree(T2);
//	PreOrderTraversal(T1, R1);
//	len = LevelOrderTraversal(T1, R1, array);
//	for (i = 0; i < len-1; i ++)
//		printf("%d ", array[i]);
//	printf("%d\n", array[i]);
//	printf("\n");
//	PreOrderTraversal(T2, R2);
//	printf("\n");
/*	if (Isomorphic(R1, R2))
		printf("Yes\n");
	else
		printf("No\n");*/
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

	scanf("%d", &N);
	for (i = 0; i < 2*N; i ++)
	{
//		fgets(input[i], 8, stdin);
		scanf("%s ", input[i].inputStr);
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
				Dir = 0;
			}
			else
			{
				StackPop(pstk, &pMid);
				if (Dir = 0)
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
		//printf("%s %d\n", input[i].inputStr, input[i].node);
	}

	

/*
	if (N <= 0)
		return Null;
	//printf("%d\n", N);
	//确认根节点的位置

	for(i = 0; i < N; i ++)
		Check[i] = 0;

	for(i = 0; i < N; i ++)
	{
		ElemType c;

	//	scanf("%c ", &c);
	//	while(c == '\n' || c == ' ') scanf("%c", &c);
		T[i].elem = 'A'+i;
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
	}*/
	/*for (i = 0; i < N; i ++)
	{
		printf("%c %d %d\n", T[i].elem, T[i].left, T[i].right);
	}*/
	return 0;//R;
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

