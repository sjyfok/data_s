/*
An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.

Figure 1
Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.
Output Specification:

For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.
Sample Input:

6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop

Sample Output:

3 4 2 6 5 1


*/
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
					StackPush(pstk, &pMid);
				}
				else
				{
					pMid->right = Tmp;					
				}
			}
			StackPush(pstk, &Tmp);
			Dir = 0;
		}
		else   //pop
		{
			if (Dir == 1)
			{
				StackPop(pstk, &pMid);
			}
			Dir = 1;
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

