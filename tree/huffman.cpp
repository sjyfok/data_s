#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXN 64
#define Yes 1
#define No  0

typedef struct TreeNode *HuffmanTree;
struct TreeNode {
    int Weight;
    HuffmanTree Left, Right;
};

/* MinHeap function */
#define MinData -1
typedef struct HeapStruct *MinHeap;
struct HeapStruct{
    HuffmanTree Data;
    int Size;
    int Capacity;
};

#define QueueSize 100
struct QNode {
    HuffmanTree Data[QueueSize];
    int rear;
    int front;
};
typedef struct QNode *Queue;

MinHeap CreateMinHeap(int MaxSize);
int MinHeapIsFull(MinHeap H);
void MinHeapInsert(MinHeap H, HuffmanTree item);
int IsEmpty(MinHeap H);
HuffmanTree DeleteMin(MinHeap H);
void PrecDown(MinHeap H, int p);
void BuildMinHeap(MinHeap H);
void PrintMinHeap(MinHeap H);
HuffmanTree Huffman(MinHeap H);
MinHeap ReadData(int num, char *ch, int *cf, MinHeap H);

void AddQ(Queue PtrQ, HuffmanTree item);
HuffmanTree DeleteQ(Queue PtrQ);
int IsEmptyQ(Queue PtrQ);
void LevelOrderTraversal(HuffmanTree HT);

MinHeap CreateMinHeap(int MaxSize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
    H->Data = (HuffmanTree)malloc(sizeof(struct TreeNode)*(MaxSize+1));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0].Weight = MinData;    //哨兵
    return H;
}

int MinHeapIsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}

void MinHeapInsert(MinHeap H, HuffmanTree item)
{
    int i;
    if(MinHeapIsFull(H)) {
        printf("Heap full");
        return;
    }
    i = ++H->Size;
    for(;H->Data[i/2].Weight>item->Weight;i=i/2) {
        H->Data[i].Weight = H->Data[i/2].Weight;
        H->Data[i].Left = H->Data[i/2].Left;
        H->Data[i].Right = H->Data[i/2].Right;
    }
    H->Data[i] = *item;
    // free(item);
}

int IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}

HuffmanTree DeleteMin(MinHeap H)
{
    int Parent, Child;
    HuffmanTree MinItem, temp;
    
    MinItem = (HuffmanTree)malloc(sizeof(struct TreeNode));
    temp = (HuffmanTree)malloc(sizeof(struct TreeNode));

    if(IsEmpty(H)) {
        printf("MinHeap Empty");
        return NULL;
    }

    *MinItem = H->Data[1];      //保存最小的元素
    *temp = H->Data[H->Size--]; //从最后一个元素插到顶点来比较
// printf("Size:%d\n", H->Size);
    for(Parent=1;Parent*2<=H->Size;Parent=Child) {  //有没有左儿子
        Child = Parent*2;       //有的话比较左儿子
        if((Child!=H->Size)&&(H->Data[Child].Weight>H->Data[Child+1].Weight))   //比较左右儿子那个小
            Child++;
        if(temp->Weight <= H->Data[Child].Weight) break;
        else {
            H->Data[Parent].Weight = H->Data[Child].Weight;
            H->Data[Parent].Left = H->Data[Child].Left;
            H->Data[Parent].Right = H->Data[Child].Right;
        }
    }
    H->Data[Parent] = *temp;
    // free(temp);
    return MinItem;
}

void PrecDown(MinHeap H, int p)
{
    int Parent, Child;
    HuffmanTree temp;

    temp = (HuffmanTree)malloc(sizeof(struct TreeNode));

    *temp = H->Data[p];         /* 取出根结点存放的值 */
    for(Parent=p;Parent*2<=H->Size;Parent=Child) {  //有没有左儿子
        Child = Parent*2;       //有的话比较左儿子
        if((Child!=H->Size)&&(H->Data[Child].Weight>H->Data[Child+1].Weight)) //比较左右儿子那个小
            Child++;
        if(temp->Weight <= H->Data[Child].Weight) break;
        else
            H->Data[Parent].Weight = H->Data[Child].Weight;
    }
    H->Data[Parent] = *temp;
}

void BuildMinHeap(MinHeap H)
{
    int i;
    /* 从最后一个结点的父结点开始，到根结点1 */
    for(i=H->Size/2;i>0;i--)
        PrecDown(H, i);
}

void PrintMinHeap(MinHeap H)
{
    int i;
// printf("MinHeap: ");
    for(i=1;i<=H->Size;i++) {
        printf(" %d", H->Data[i].Weight);
    }
    printf("\n");
}

HuffmanTree Huffman(MinHeap H)
{
    /* 假设H->Size个权值已经存在H->Elements[]->Weight里 */
    int i;
    HuffmanTree T;
    BuildMinHeap(H);        /* 将H->Elemnts[]按权值调整为最小堆 */
// PrintMinHeap(H);
    for(i=1;i<H->Size;) {
        T = (HuffmanTree)malloc(sizeof(struct TreeNode));   /* 建立新结点 */
        T->Left = DeleteMin(H);         /* 从最小堆中删除一个结点，作为新T的左子结点 */
        T->Right = DeleteMin(H);        /* 从最小堆中删除一个结点，作为新T的右子结点 */
        T->Weight = T->Left->Weight+T->Right->Weight;   /* 计算新权值 */
        MinHeapInsert(H, T);
// PrintMinHeap(H);
// printf("Huffman:");
// LevelOrderTraversal(T);
// printf("\n");
    }
    T = DeleteMin(H);
    return T;
}

void PrintHuffman(HuffmanTree HT)
{
    if(HT) {
        PrintHuffman(HT->Left);
        PrintHuffman(HT->Right);
        printf("%d ", HT->Weight);
    }
}

MinHeap ReadData(int num, char *ch, int *cf, MinHeap H)
{
    int i;
    for(i=0;i<num;i++) {
        if(i==num-1)
            scanf("%c %d", &ch[i], &cf[i]);
        else
            scanf("%c %d ", &ch[i], &cf[i]);
        HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TreeNode));
        T->Weight = cf[i];
        MinHeapInsert(H, T);
    }
    return H;
}

int WPL(HuffmanTree T, int Depth)
{
// printf("T->Weight = %d, T->Left = %p, T->Right =%p\n", 
    // T->Weight, T->Left, T->Right);
    int rw=0, lw=0;
    if(!T->Left && !T->Right)
        return (Depth*(T->Weight));
    else {
        if(T->Left) lw = WPL(T->Left, Depth+1);
        if(T->Right) rw = WPL(T->Right, Depth+1);
        return lw+rw;
    }
}

HuffmanTree CreateHuffmanTree()
{
    HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TreeNode));
    T->Weight = 0;
    T->Left = T->Right = NULL;
    return T;
}

void DeleteHuffmanTree(HuffmanTree T)
{
    if(T) {
        DeleteHuffmanTree(T->Left);
        DeleteHuffmanTree(T->Right);
        free(T);
    }
}

int Judge(int N, int CodeLen, char *ch, int *cf)
{
    char s1[MAXN], s2[MAXN];
    int i, j, weight, flag = Yes;
    HuffmanTree T = CreateHuffmanTree();
    HuffmanTree pt = NULL;
    for(i=0;i<N;i++) {
        scanf("%s %s\n", s1, s2);
        if(strlen(s2) > N) 
		{ 
			flag = No; 
			break; 
		}
        for(j=0;s1[0]!=ch[j];j++)
            if(j==N)  { flag = No; break; }
        weight = cf[j];
        pt = T;
        for(j=0;j<strlen(s2);j++) {
            if(s2[j] == '0') {                      //开始创建树
                if(!pt->Left) pt->Left = CreateHuffmanTree();   //没有就创建
                else if(pt->Left->Weight != 0) {
                    // printf("Exit from pt->Left->Weight == 1\n");
                    flag = No;        //是否路过叶子
                } 
                pt = pt->Left;
            } else if(s2[j] == '1') {
                if(!pt->Right) pt->Right = CreateHuffmanTree();
                else if(pt->Right->Weight != 0) {
                    // printf("Exit from pt->Right->Weight == 1\n");
                    flag = No;
                }
                pt = pt->Right;
            } else {                                //应该不会发生
                // printf("Exit from not happen\n");
                flag = No;
            }
        }
        pt->Weight = weight;                        //叶子标记
        weight = 0;                                 //清空weight
        if(pt->Left || pt->Right) {
            // printf("Exit from pt->Left || pt->Right\n");
            flag = No;     //不是叶子也错
        }
    }
    if(flag != No && CodeLen == WPL(T, 0)) {
        return Yes;
    } else {
        // printf("Exit from CodeLen != WPL(T, 0) %d\n", WPL(T, 0));
        if(T) DeleteHuffmanTree(T);
        return No;
    }
}

int main()
{
    int N, CodeLen, n, i;          //huffman的叶子结点个数,WPL最优值
    MinHeap H;      //最小堆
    char *ch;       //输入的字符组
    int *cf;
    HuffmanTree T;  //HuffmanTree
    scanf("%d\n", &N);
    H = CreateMinHeap(N);
    ch = (char *)malloc(sizeof(char)*N);
    cf = (int *)malloc(sizeof(int)*N);
    H = ReadData(N, ch, cf, H);
    T = Huffman(H);
    CodeLen = WPL(T, 0);
    scanf("%d\n", &n);
    for(i=0;i<n;i++) {
        if(Judge(N, CodeLen, ch, cf))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}