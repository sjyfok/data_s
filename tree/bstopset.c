/*
本题要求实现给定二叉搜索树的5种常用操作。
函数接口定义：

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

其中BinTree结构定义如下：

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

    函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针；
    函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；如果X不在树中，则打印一行Not Found并返回原树的根结点指针；
    函数Find在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针；
    函数FindMin返回二叉搜索树BST中最小元结点的指针；
    函数FindMax返回二叉搜索树BST中最大元结点的指针。

裁判测试程序样例：

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

//void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 *///
//void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */
/*
BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
*/
/* 你的代码将被嵌在这里 */
/*
输入样例：

10
5 8 6 2 4 1 0 10 9 7
5
6 3 10 0 5
5
5 7 0 10 3

输出样例：

Preorder: 5 2 1 0 4 8 6 7 10 9
6 is found
3 is not found
10 is found
10 is the largest key
0 is found
0 is the smallest key
5 is found
Not Found
Inorder: 1 2 4 6 8 9


*/


#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); 
void InorderTraversal( BinTree BT );  

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); 
		PreorderTraversal(BST); 
		printf("\n");

    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}


//先序遍历树
void PreorderTraversal(BinTree BT)
{
	if (BT != NULL)
	{
		printf("%d ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}
//中序遍历树
void InorderTraversal( BinTree BT )
{
	if (BT != NULL)
	{
		InorderTraversal(BT->Left);
		printf("%d ", BT->Data);
		InorderTraversal(BT->Right);
	}

}

BinTree Insert( BinTree BST, ElementType X )
{
	if (!BST)
	{
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else if (X < BST->Data) {
		BST->Left = Insert(BST->Left, X);
	} else {
		BST->Right = Insert(BST->Right, X);
	}
	return BST;
}

Position FindMin( BinTree BST )
{
	if (BST != NULL)
	{
		while (BST->Left != NULL)
		{
			BST = BST->Left;
		}
	}
	return BST;
}

Position FindMax( BinTree BST )
{
	if (BST != NULL)
	{
		while (BST->Right != NULL) 
		{
			BST = BST->Right;
		}
	}
	return BST;
}

Position Find( BinTree BST, ElementType X )
{
	if (BST == NULL)
		return NULL;
	if (BST->Data < X) //在右子树中找
	{
		return Find(BST->Right, X);
	}
	else if (BST->Data > X)
	{
		return Find(BST->Left, X);
	}
	else
		return BST;
}

BinTree Delete( BinTree BST, ElementType X )
{
	if (BST == NULL) //没有找到
	{
		printf("Not Found\n");
		return NULL;
	}
	if (BST->Data < X)
	{
		BST->Right =  Delete(BST->Right, X);
	}
	else if (BST->Data > X)
	{
		BST->Left =  Delete(BST->Left, X);
	}
	else 
	{
		Position Tmp;
		if (BST->Left && BST->Right) //有左右孩子
		{
			Tmp = FindMin(BST->Right);
			BST->Data = Tmp->Data;
			BST->Right = Delete(BST->Right, BST->Data);
		}
		else
		{
			Tmp = BST;
			if (BST->Left == NULL)
				BST = BST->Right;
			else if (BST->Right == NULL)
				BST = BST->Left;
			free(Tmp);
		}
	}
	
	return BST;
}
