/*

*/


#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *HuffmanTree;
typedef struct TNode *Tree;

struct TNode{
    int weight;
	struct TNode* Left;
    struct TNode* Right;
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
void DisplayHeap(MinHeap H);
void FreeHeap(MinHeap H);
int IsFull(MinHeap H);
int IsEmpty(MinHeap H);
int Insert(MinHeap H, ElemType X);
ElemType* DeleteMin(MinHeap H);





//////////////////////////////////////////////////

HuffmanTree Huffman(MinHeap H);
void PreorderTraversal( HuffmanTree BT ); 
int WPL(HuffmanTree HT, int depth);
int Judge(int aCnt, int hCode, char text[], int hz[]);
Tree BuildTree();
void DestroyTree(Tree T);
int JudgeTree(Tree T, int Hz);

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
  //  PreorderTraversal(T); 
	fflush(stdout);
	huffmanCodeLen = WPL(T, 0);
//	printf("codelen = %d\n", huffmanCodeLen);
	scanf("%d", &M);
	while (M --)
	{
		if (Judge(N, huffmanCodeLen, pText, pHz))printf("Yes\n");
		else printf("No\n");
	}
	
    free(pHz);
    free(pText);
    FreeHeap(H);
    
	fflush(stdout);
    return 0;
}

char answer[MaxSize];

Tree BuildTree()
{
	Tree elem = malloc(sizeof(struct TNode));
	elem->weight = 0;
	elem->Right = elem->Left = NULL;

	return elem;
}

int JudgeTree(Tree T, int Hz)
{
	int len = strlen(answer);
	int i;
	Tree CurT = T;

	for (i = 0; i < len; i++)
	{
		if (answer[i] == '1')
		{
			if (CurT->Right == NULL)
			{
				Tree TempT = malloc(sizeof(struct TNode));
				TempT->Left = TempT->Right = NULL;
				TempT->weight = 0;
				CurT->Right = TempT;
			}
			else if (CurT->Right->weight != 0)
			{
				return 0;
			}
			CurT = CurT->Right;
		}
		if (answer[i] == '0')
		{
			if (CurT->Left == NULL)
			{
				Tree TempT = malloc(sizeof(struct TNode));
				TempT->Left = TempT->Right = NULL;
				TempT->weight = 0;
				CurT->Left = TempT;
			}
			else if (CurT->Left->weight != 0)
			{
				return 0;
			}
			CurT = CurT->Left;
		}
	}
	
	////有误
	//if (CurT->weight != 0)
	//{
	//	return 0;
	//}
	if (CurT->Left == NULL && CurT->Right == NULL)
	{
		CurT->weight = Hz;
		return 1;
	}
	else
		return 0;
	
//	return 1;
}



void DestroyTree(Tree T)
{

	if (T != NULL)
	{
		//		printf("%d ", BT->weight);
		DestroyTree(T->Left);
		DestroyTree(T->Right);
		free(T);
	}

	//if (T->Left == NULL && T->Right  == NULL)
	//{
	//	free(T);
	//}
	//DestroyTree(T->Left);
	//DestroyTree(T->Right);
	
}




int Judge(int aCnt, int hCode, char text[], int hz[])
{
	//char s1[2];
	//int i, j, weight, flag = 1;
	//Tree T = BuildTree();
	//Tree pt = NULL;
	//int N = aCnt;
	//for (i = 0; i< N; i++) {
	//	scanf("%s %s\n", s1, answer);
	//	if (strlen(answer) > N) { flag = 0; break; }
	//	for (j = 0; s1[0] != text[j]; j++)
	//		if (j == N) { flag = 0; break; }
	//	weight = hz[j];
	//	pt = T;
	//	for (j = 0; j<strlen(answer); j++) {
	//		if (answer[j] == '0') {                      //开始创建树
	//			if (!pt->Left) pt->Left = BuildTree();   //没有就创建
	//			else if (pt->Left->weight != 0) {
	//				// printf("Exit from pt->Left->Weight == 1\n");
	//				flag = 0;        //是否路过叶子
	//			}
	//			pt = pt->Left;
	//		}
	//		else if (answer[j] == '1') {
	//			if (!pt->Right) pt->Right = BuildTree();
	//			else if (pt->Right->weight != 0) {
	//				// printf("Exit from pt->Right->Weight == 1\n");
	//				flag = 0;
	//			}
	//			pt = pt->Right;
	//		}
	//		else {                                //应该不会发生
	//											  // printf("Exit from not happen\n");
	//			flag = 0;
	//		}
	//	}
	//	pt->weight = weight;                        //叶子标记
	//	weight = 0;                                 //清空weight
	//	if (pt->Left || pt->Right) {
	//		// printf("Exit from pt->Left || pt->Right\n");
	//		flag = 0;     //不是叶子也错
	//	}
	//}
	//if (flag != 0 && hCode == WPL(T, 0)) {
	//	return 1;
	//}
	//else {
	//	// printf("Exit from CodeLen != WPL(T, 0) %d\n", WPL(T, 0));
	//	if (T) DestroyTree(T);
	//	return 0;
	//}

	int i, len, wpl = 0, N = aCnt, j;
	int skip = 1;
	char s1[2];
	Tree T = BuildTree();
	for (i = 0; i < aCnt; i++)
	{
		if (!skip)
		{
			scanf("%s%s", s1, answer);
			continue;
		}
		scanf("%s%s", s1, answer);
		len = strlen(answer);
		if (len > N)
		{
			skip = 0;
			continue;
		}
		for (j = 0; s1[0] != text[j]; j++);
		if (j >= N)
		{
			skip = 0;
			continue;
		}
		wpl += hz[j] * len;
		skip = JudgeTree(T, hz[j]);
	}
	DestroyTree(T);
	if (skip == 0)
	{
		return 0;
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
