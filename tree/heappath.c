/*
将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。
输入格式:

每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M个下标。
输出格式:

对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字间以1个空格分隔，行末不得有多余空格。
输入样例:

5 3
46 23 26 24 10
5 4 3

输出样例:

24 23 10
46 23 10
26 10


*/
#include <stdio.h>
#include <stdlib.h>

#define		MaxSize		1001
typedef int ElemType;

typedef struct HNODE *Heap;
struct HNODE {
	ElemType *Data;
	int Size;
	int Capacity;
};

#define MAXDATA 10001
#define MINDATA -10001
typedef Heap    MaxHeap;
typedef Heap    MinHeap;


MaxHeap CreateHeap(int maxsize);
void BuildHeap(MinHeap H);
void DisplayHeap(MinHeap H);
void PrintPath(MinHeap H, int start);
void FreeHeap(MinHeap H);
int Insert(MinHeap H, ElemType X);


int main(void)
{
	int N, M, i;

	int *path;
    MinHeap H;
    ElemType e;
	/////////////////////////////////
	//读取测试数据
/*	FILE *fp = fopen("test.file", "r");
	fscanf(fp, "%d %d", &N, &M);
	printf("N= %d M= %d\n", N, M);
    */
    scanf("%d %d", &N, &M);
    
    H = CreateHeap(N);
    path = (ElemType*)malloc(sizeof(ElemType)*M);

/*	for (i = 0; i < N; i ++)
    {
		fscanf(fp, "%d", H->Data+i+1);  
        H->Size ++;
    } */
	for (i = 0; i < N; i ++)
    {
	//	scanf("%d", H->Data+i+1);//&e);  
     //   H->Size ++;
     //
     //
        scanf("%d", &e);
        Insert(H, e);
    }

    for(i = 0; i < M; i ++)
        scanf("%d", path+i);
/*    for(i = 0; i < M; i ++)
        printf("%d ", *(path+i));
    printf("\n");*/

 //   DisplayHeap(H);
//    BuildHeap(H);
  //  DisplayHeap(H);
    for(i = 0; i < M; i ++)
        PrintPath(H, *(path+i));

	/////////////////////////////////
	//读入输入序列
/*	scanf("%d", &N);
	for (i = 0; i < N; i ++) {
		scanf("%d", &inser[i]); 
	}
    */
	//对输入数据进行排序
	//SortInc(inser, N);
//	qsort(inser, N, sizeof(TElemType), cmp);
	//DispSort(inser, N);
/*	T = BuildTree(inser, N);
  LevelOrderTraversal(T, trav);
	for (i = 0; i < N-1; i ++)
		printf("%d ", trav[i]);
	printf("%d\n", trav[i]);
*/
    free(path);
    FreeHeap(H);
	return 0;
}

int IsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}

int Insert(MinHeap H, ElemType X)
{
    int i;
    if (IsFull(H))
    {
        return 0;
    }
    i = ++H->Size;
    for(; H->Data[i/2] > X; i/=2)
        H->Data[i] = H->Data[i/2];
    H->Data[i] = X;
    return 1;
}

void FreeHeap(MinHeap H)
{
    free(H->Data);
    free(H);
}

void PrintPath(MinHeap H, int start)
{
    int i;
    for (i = start; i > 1; i = i/2)
        printf("%d ", H->Data[i]);
    printf("%d", H->Data[i]);
    printf("\n");
}

MaxHeap CreateHeap(int maxsize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNODE));

    H->Data = (ElemType*)malloc((maxsize+1)*sizeof(ElemType));
    H->Size = 0;
    H->Capacity = maxsize;
    H->Data[0] = MINDATA;

    return H;
}

void PercDown(MinHeap H, int p)
{
    int parent, child;

    ElemType x;
    x = H->Data[p];

    for(parent = p; parent*2<=H->Size; parent = child)
    {
        child = parent*2;
        if((child != H->Size) && (H->Data[child] > H->Data[child+1]))
            child ++;
        if (x <= H->Data[child]) break;
        else
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = x;

    //DisplayHeap(H);
}

void BuildHeap(MinHeap H)
{
    int i;
    for(i = H->Size/2; i > 0; i --)
        PercDown(H, i);
}

void DisplayHeap(MinHeap H)
{
    int i;
    for (i = 1; i <= H->Size; i ++)
        printf("%d ", *(H->Data+i));
    printf("\n");
}
