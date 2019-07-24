/*

*/
//#include <stdio.h>
//#include <stdlib.h>

#include <iostream>
#include <string.h>

using namespace std;
typedef struct TNode *HuffmanTree;

struct TNode{
    int weight;
	int swap;
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
int IsEmpty(MinHeap H);
int Insert(MinHeap H, ElemType X);
ElemType* DeleteMin(MinHeap H);





//////////////////////////////////////////////////

HuffmanTree Huffman(MinHeap H);
void PreorderTraversal( HuffmanTree BT ); 
void Judge(HuffmanTree T, int hz[], int N);
//void InorderTraversal( HuffManTree BT );  

//BinTree Insert( BinTree BST, ElementType X );
//BinTree Delete( BinTree BST, ElementType X );
//Position Find( BinTree BST, ElementType X );
//Position FindMin( BinTree BST );
//Position FindMax( BinTree BST );

int main()
{
    MinHeap H;
    int N, i;
    char *pText;
    int *pHz;
    ElemType *pelem;
    HuffmanTree T;

	cin >> N;
    pText = (char*)malloc(sizeof(char)*N);
    pHz = (int*)malloc(sizeof(int)*N);
    
    H = CreateHeap(N);
	for (i = 0; i < N; i ++)
    {
      
		cin >> *(pText + i);
		if (i == (N - 1))
			//scanf("%d", pHz+i);
			cin >> *(pHz + i);
		else
			//scanf("%d ", pHz+i);
			cin >> *(pHz + i);
        pelem = (ElemType*)malloc(sizeof(ElemType));
        pelem->weight = *(pHz+i);
		pelem->swap = 0;
        pelem->Left = NULL;
        pelem->Right = NULL;
        Insert(H, *pelem);
    }
   // DisplayHeap(H);
    T = Huffman(H);
    PreorderTraversal(T); 

	Judge(T, pHz, N);

    free(pHz);
    free(pText);
    FreeHeap(H);
    
  	fflush(stdout);
    return 0;
}

static char  answer[MaxSize];

int JudgeDo(char ch,  HuffmanTree T, int hz)
{
	int i;
	HuffmanTree RT1, RT2, tempT;
	int len = strlen(answer);
	
	RT2 = RT1 = T;
	for (i = 0; i < len; i++)
	{
		if (answer[i] == '0')
		{
			if (RT2->Left)
			{
				RT1 = RT2;
				RT2 = RT2->Left;		
			}
			else
			{
<<<<<<< HEAD
				if (RT1->Right && RT1->swap == 0)
=======
				if (RT1->swap == 0)
>>>>>>> 7d27296f85e1c6f70d3f4bdf2d942c5ee164fe5d
				{
					tempT = RT1->Left;
					RT1->Left = RT1->Right;
					RT1->Right = tempT;
					if (RT2 == RT1->Left)
						RT2 = RT1->Right;
					else RT2 = RT1->Left;
					RT1->swap = 1;
				}
				else return 0;
				if (RT2->Left)
				{
					RT1 = RT2;
					RT2 = RT2->Left;
				}
				else return 0;
				
			}
		}
		else if (answer[i] == '1')
		{
			if (RT2->Right)
			{
				RT1 = RT2;
				RT2 = RT2->Right;
			}
			else
			{
				if (RT1->swap == 0)
				{
					tempT = RT1->Left;
					RT1->Left = RT1->Right;
					RT1->Right = tempT;
					if (RT2 == RT1->Left)
						RT2 = RT1->Right;
					else RT2 = RT1->Left;
					RT1->swap = 1;
				}
				else return 0;
				if (RT2->Right)
				{
					RT1 = RT2;
					RT2 = RT2->Right;
				}
				else return 0;
			}
		}
	}
	if (RT2->Left || RT2->Right)
		return 0;
	if (RT2->weight == hz)
		return 1;
	return 0;
}



void Judge(HuffmanTree T, int hz[], int N)
{
	int i, M, j;
	char szCh;
	
	rewind(stdin);
	cin >> M;
	//scanf("%d", &M);
	getchar();
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			//scanf("%s %s\n", &szCh, answer);
			cin >> szCh >> answer;
		//	getchar();
			
			if (JudgeDo(szCh, T, hz[j]) == 0) {
				printf("no\n");
				break;
			}
		}
		if (j >= N)
			printf("yes\n");
		PreorderTraversal(T);
	}
}

HuffmanTree Huffman(MinHeap H)
{
    int i; 
    HuffmanTree T;

    while(!IsEmpty(H)) {
        T = (TNode*)malloc(sizeof(struct TNode));
        T->Left = DeleteMin(H);   
    //    DisplayHeap(H);
        T->Right = DeleteMin(H);
     //   DisplayHeap(H);
        T->weight = T->Left->weight+T->Right->weight;
		T->swap = 0;
     //   printf("weight = %d\n", T->weight);
		if (!IsEmpty(H))  //当堆空的时候 就完成堆的创建
			Insert(H, *T);
     //   DisplayHeap(H);
    }
  //  T = DeleteMin(H);
  //  DisplayHeap(H);
    return T;
}

//先序遍历树
void PreorderTraversal(HuffmanTree BT)
{

	if (BT != NULL)
	{
		printf("%d ", BT->weight);
		BT->swap = 0;
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}


MaxHeap CreateHeap(int maxsize)
{
	MinHeap H = (MinHeap)malloc(sizeof(struct HNODE));

	H->Data = (ElemType*)malloc((maxsize + 1) * sizeof(ElemType));
	H->Size = 0;
	H->Capacity = maxsize;
	// H->Data[0] = MINDATA;

	return H;
}


void DisplayHeap(MinHeap H)
{
	int i;
	for (i = 1; i <= H->Size; i++)
		printf("%d ", ((ElemType*)(H->Data + i))->weight);
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
	for (; H->Data[i / 2].weight > X.weight; i /= 2)
		H->Data[i] = H->Data[i / 2];
	H->Data[i] = X;
	return 1;
}

void FreeHeap(MinHeap H)
{
	free(H->Data);
	free(H);
}

int IsFull(MinHeap H)
{
	return (H->Size == H->Capacity);
}


int IsEmpty(MinHeap H)
{

	return (H->Size == 0);
}

ElemType* DeleteMin(MinHeap H)
{
	int Parent, Child;

	ElemType  X;
	ElemType *pMinItem = (ElemType*)malloc(sizeof(ElemType));

	//   if (IsEmpty(H)) {
	//       return ;
	//    }
	*pMinItem = H->Data[1];
	X = H->Data[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
	{
		Child = 2 * Parent;
		if ((Child != H->Size) && (H->Data[Child].weight > H->Data[Child + 1].weight))
			Child++;
		if (X.weight <= H->Data[Child].weight)
			break;
		else
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
	return pMinItem;
}

/*
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


