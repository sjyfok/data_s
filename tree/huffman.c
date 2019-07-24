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
int IsEmpty(MinHeap H);
int Insert(MinHeap H, ElemType X);
ElemType* DeleteMin(MinHeap H);





//////////////////////////////////////////////////

HuffmanTree Huffman(MinHeap H);
void PreorderTraversal( HuffmanTree BT ); 
int WPL(HuffmanTree HT, int depth);

int Judge(int aCnt, int hCode, int hz[]);

int main()
{
    MinHeap H;
    int N, M, i;
    char *pText;
    int *pHz;
    ElemType *pelem;
    HuffmanTree T;
	int huffmanCodeLen;
    scanf("%d", &N);
	getchar();
    pText = (char*)malloc(sizeof(char)*N);
    pHz = (int*)malloc(sizeof(int)*N);
    
    H = CreateHeap(N);
	for (i = 0; i < N; i ++)
    {
        scanf("%c ", pText+i);
        if (i == (N-1))
            scanf("%d", pHz+i);
        else
            scanf("%d ", pHz+i);
        pelem = malloc(sizeof(ElemType));
        pelem->weight = *(pHz+i);
        pelem->Left = NULL;
        pelem->Right = NULL;
        Insert(H, *pelem);
    }
 //   DisplayHeap(H);
    T = Huffman(H);
    PreorderTraversal(T); 
	fflush(stdout);
	huffmanCodeLen = WPL(T, 0);
//	printf("codelen = %d\n", huffmanCodeLen);
	scanf("%d", &M);
	while (M --)
	{
		if (Judge(N, huffmanCodeLen, pHz))printf("Yes\n");
		else printf("No\n");
	}
	
    free(pHz);
    free(pText);
    FreeHeap(H);
    
	fflush(stdout);
    return 0;
}

char answer[MaxSize];

int Judge(int aCnt, int hCode, int hz[])
{
	int i, len, wpl = 0;
	char s1[2];
	for (i = 0; i < aCnt; i++)
	{
		scanf("%s%s", s1, answer);
		len = strlen(answer);
		wpl += hz[i] * len;
	}

	if (wpl != hCode)
	{
		return 0;
	}

	return 1;

}

HuffmanTree Huffman(MinHeap H)
{
    int i; 
    HuffmanTree T;

    while(!IsEmpty(H)) {
        T = malloc(sizeof(struct TNode));
        T->Left = DeleteMin(H);      
        T->Right = DeleteMin(H);  
        T->weight = T->Left->weight+T->Right->weight;   
		if (!IsEmpty(H))  //当堆空的时候 就完成堆的创建
			Insert(H, *T); 
    }

    return T;
}

//先序遍历树
void PreorderTraversal(HuffmanTree BT)
{

	if (BT != NULL)
	{
//		printf("%d ", BT->weight);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}

//计算wpl
int WPL(HuffmanTree HT, int depth)
{
	if (!HT->Left && !HT->Right)
	{
		return (depth*HT->weight);
	}
	else
	{
		int lwpl = 0, rwpl = 0;
		lwpl = WPL(HT->Left, depth + 1);
		rwpl = WPL(HT->Right, depth + 1);

		return (lwpl+rwpl);
	}
}

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
    ElemType *pMinItem = malloc(sizeof(ElemType));

 //   if (IsEmpty(H)) {
 //       return ;
//    }
    *pMinItem = H->Data[1];
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
    return pMinItem;
}
