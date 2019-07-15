/*

*/


#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *HuffmanTree;

struct TNode{
    int weight;
    HuffmanTree Left;
    HuffmanTree Right;
};


#define		MaxSize		1001
typedef struct TNode ElemType;

typedef struct HNODE *Heap;
struct HNODE {
	ElemType *Data;
	int Size;
	int Capacity;
};

#define  MINDATA 0

typedef Heap    MaxHeap;
typedef Heap    MinHeap;


MaxHeap CreateHeap(int maxsize);
void BuildHeap(MinHeap H);
void DisplayHeap(MinHeap H);
void PrintPath(MinHeap H, int start);
void FreeHeap(MinHeap H);
int IsFull(MinHeap H);
int Insert(MinHeap H, ElemType X);
ElemType DeleteMin(MinHeap H);





//////////////////////////////////////////////////

HuffmanTree Huffman(MinHeap H);
//void PreorderTraversal( HuffmanTree BT ); 
//void InorderTraversal( HuffManTree BT );  

//BinTree Insert( BinTree BST, ElementType X );
//BinTree Delete( BinTree BST, ElementType X );
//Position Find( BinTree BST, ElementType X );
//Position FindMin( BinTree BST );
//Position FindMax( BinTree BST );

int main()
{
    MinHeap H;
    int M, i;
    char *pText;
    int *pHz;
    ElemType *pelem;

    scanf("%d\n", &M);
    pText = (char*)malloc(sizeof(char)*M);
    pHz = (int*)malloc(sizeof(int)*M);
    
    H = CreateHeap(M);
	for (i = 0; i < M; i ++)
    {
        scanf("%c ", pText+i);
        if (i == (M-1))
            scanf("%d", pHz+i);
        else
            scanf("%d ", pHz+i);
        pelem = malloc(sizeof(ElemType));
        pelem->weight = *(pHz+i);
        pelem->Left = NULL;
        pelem->Right = NULL;
        Insert(H, *pelem);
    }
    DisplayHeap(H);

    free(pHz);
    free(pText);

    
  /*  BinTree BST, MinP, MaxP, Tmp;
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

    return 0;*/
}

HuffmanTree Huffman(MinHeap H)
{
    int i; 
    ElemType weight;
    HuffmanTree T, HuffManNode;

    for (i = 1; i < H->Size; i ++)
    {
        T = malloc(sizeof(struct TNode));
        T->Left = &DeleteMin(H);   
        T->Right = &DeleteMin(H);
        T->weight = T->Left->weight+T->Right->weight;
        Insert(H, T);
    }
    T = &DeleteMin(H);
    return T;
}

//先序遍历树
/*void PreorderTraversal(BinTree BT)
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
*/


MaxHeap CreateHeap(int maxsize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNODE));

    H->Data = (ElemType*)malloc((maxsize+1)*sizeof(ElemType));
    H->Size = 0;
    H->Capacity = maxsize;
   // H->Data[0] = MINDATA;

    return H;
}


void DisplayHeap(MinHeap H)
{
    int i;
    for (i = 1; i <= H->Size; i ++)
        printf("%d ", ((ElemType*)(H->Data+i))->weight);
    printf("\n");
}

int Insert(MinHeap H, ElemType X)
{
    int i;
    if (IsFull(H))
    {
        return 0;
    }
    i = ++H->Size;
    for(; H->Data[i/2].weight > X.weight; i/=2)
        H->Data[i] = H->Data[i/2];
    H->Data[i] = X;
    return 1;
}

int IsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}

int IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}

ElemType DeleteMin(MinHeap H)
{
    int Parent, Child;

    ElemType MinItem, X;

 //   if (IsEmpty(H)) {
 //       return ;
//    }
    MinItem = H->Data[1];
    X = H->Data[H->Size--];
    for (Parent = 1; Parent*2 <= H->Size; Parent = Child)
    {
        Child = 2*Parent;
        if((Child != H->Size)&&(H->Data[Child].weight > H->Data[Child+1].weight))
            Child ++;
        if (X.weight <= H->Data[Child].weight)
            break;
        else
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;
}
