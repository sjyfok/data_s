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

