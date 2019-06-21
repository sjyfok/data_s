/*
本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。
函数接口定义：

List Merge( List L1, List L2 );

其中List结构定义如下：
*/
//typedef struct Node *PtrToNode;
//struct Node {
//    ElementType Data; /* 存储结点数据 */
 //   PtrToNode   Next; /* 指向下一个结点的指针 */
//};
//typedef PtrToNode List; /* 定义单链表类型 */
/*
L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Merge要将L1和L2合并为一个非递减的整数序列。应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。
裁判测试程序样例：

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;
*/
//List Read(); /* 细节在此不表 */
//void Print( List L ); /* 细节在此不表；空链表将输出NULL */
/*
List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}
*/
/* 你的代码将被嵌在这里 */



#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); 
void Print( List L ); 

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read()
{
	int num, i;
	List Header = NULL, TPtr = NULL, NPtr = NULL;

	scanf("%d", &num);
	if (num == 0)
	{
		return NULL;
	}
	if ((Header = (List)malloc(sizeof(struct Node))) == NULL)
		return NULL;
	Header->Next = NULL;
	TPtr = Header;
	for (i = 0; i < num; i ++)
	{
		if ((NPtr = (List)malloc(sizeof(struct Node))) != NULL)
		{
			scanf("%d", &NPtr->Data);
			NPtr->Next = NULL;
			TPtr->Next = NPtr;
			TPtr = TPtr->Next;
		}
	}

	return Header;
}

void Print( List L ) 
{
	List Ptr;
	Ptr = L->Next;
	if (Ptr== NULL)
		printf("NULL\n");
	else
	{
		while (Ptr->Next != NULL)
		{
			printf("%d ", Ptr->Data);
			Ptr = Ptr->Next;
		}
		printf("%d\n", Ptr->Data);
	}
}

List Merge( List L1, List L2 )
{
	List Header = NULL, L1Ptr = L1, L2Ptr = L2, LPtr = NULL;

	Header = (List)malloc(sizeof(struct Node));
	if (L1Ptr->Next == NULL && L2Ptr == NULL)
		Header->Next = NULL;
	else if (L1Ptr->Next == NULL)
	{
		Header->Next = L2->Next;
		L2->Next = NULL;
	} 
	else if (L2Ptr->Next == NULL)
	{
		Header->Next = L1->Next;
		L1->Next = NULL;
	}
	else 
	{
		LPtr = Header;
		L1Ptr = L1Ptr->Next;
		L2Ptr = L2Ptr->Next;
		while(L1Ptr != NULL && L2Ptr != NULL)
		{
			if (L1Ptr->Data > L2Ptr->Data)
			{
				LPtr->Next = L2Ptr;
				L2Ptr = L2Ptr->Next;
			}
			else 
			{
				LPtr->Next = L1Ptr;
				L1Ptr = L1Ptr->Next;
			}
			LPtr = LPtr->Next;
//			printf("\nData = %d", LPtr->Data);
		}
		if (L1Ptr != NULL)
		{
			LPtr->Next = L1Ptr;
		}
		else 
		{
			LPtr->Next = L2Ptr;
		}

		L1->Next = NULL;
		L2->Next = NULL;
	}

	return Header;


}

