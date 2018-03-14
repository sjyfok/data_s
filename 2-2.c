#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode * Polynomial;

struct PolyNode{
	int coef;
	int expon;
	Polynomial link;
}; 

Polynomial ReadPoly(void);
void PrintPoly(Polynomial poly);
Polynomial SumOfPoly(Polynomial A, Polynomial B);
Polynomial MulOfPoly(Polynomial A, Polynomial B);

int main(void)
{
	Polynomial A, B, S, M;

	A = ReadPoly();
	B = ReadPoly();
	S = SumOfPoly(A, B);
	M = MulOfPoly(A, B);
//	PrintPoly(M);
//	PrintPoly(S);
//	PrintPoly(A);
	return 0;
}

Polynomial MulOfPoly(Polynomial A, Polynomial B)
{
	Polynomial Header = NULL, MHPtr = NULL, MPtr = NULL, SPtr = NULL, TPtr = NULL,
		APtr = A->link, BPtr = B->link, TMPPtr = NULL;
	
	Header = (Polynomial)malloc(sizeof(struct PolyNode));
	Header->link = NULL;
	SPtr = Header;
	MHPtr = (Polynomial)malloc(sizeof(struct PolyNode));
	MPtr = MHPtr;
	while (APtr != NULL)
	{
		BPtr = B->link;
		while (BPtr != NULL)
		{
			TPtr = (Polynomial)malloc(sizeof(struct PolyNode));
			TPtr->link = NULL;
			TPtr->coef = APtr->coef*BPtr->coef;
			TPtr->expon = APtr->expon+BPtr->expon;
			MPtr->link = TPtr;
			MPtr = TPtr;
			BPtr = BPtr->link;
		}
		if (SPtr->link) 
		{  //alu sum
			TMPPtr = SPtr;
			SPtr = SumOfPoly(TMPPtr, MHPtr);
			//realse MPtr
			MPtr = MHPtr->link;
			while(MPtr)
			{
				TMPPtr = MPtr->link;		
				free(MPtr);
				MPtr = TMPPtr;
			}
			MHPtr->link = NULL;
			MPtr = MHPtr;
		} 
		else
		{
			SPtr = MHPtr;
	//		PrintPoly(SPtr);
		}
		APtr = APtr->link;
	}

	return SPtr;
}

Polynomial SumOfPoly(Polynomial A, Polynomial B)
{
	Polynomial Header = NULL;
	Polynomial APtr = A->link, BPtr = B->link, TPtr = NULL, RPtr = NULL, PPtr;

	Header = (Polynomial)malloc(sizeof(struct PolyNode));
	Header->link = TPtr;
	PPtr = Header;

	while(APtr != NULL && BPtr != NULL)
	{
		TPtr = (Polynomial)malloc(sizeof(struct PolyNode));
		TPtr->link = NULL;
		if (APtr->expon > BPtr->expon)
		{
			TPtr->expon = APtr->expon;
			TPtr->coef = APtr->coef;
			APtr = APtr->link;
		} else if (APtr->expon < BPtr->expon)
		{
			TPtr->expon = BPtr->expon;
			TPtr->coef = BPtr->coef;
			BPtr = BPtr->link;
		} else 
		{
			TPtr->expon = BPtr->expon;
			TPtr->coef = APtr->coef+BPtr->coef;
			APtr = APtr->link;
			BPtr = BPtr->link;
		}
		PPtr->link = TPtr;
		PPtr = TPtr;
	}
	if (BPtr != NULL)
	{
		RPtr = BPtr;
	} 
	else if (APtr != NULL) 
	{
		RPtr = APtr;
	}
	while (RPtr)
	{
		TPtr = (Polynomial)malloc(sizeof(struct PolyNode));
		TPtr->link = NULL;
		TPtr->expon = RPtr->expon;
		TPtr->coef = RPtr->coef;
		PPtr->link = TPtr;
		PPtr = TPtr;
		RPtr = RPtr->link;
	}
	return Header;
}

Polynomial ReadPoly(void)
{
	int num;
	Polynomial Header, NPtr, TPtr;
	scanf("%d", &num);
	if(num < 0)
		return NULL;
	Header = (Polynomial)malloc(sizeof(struct PolyNode));
	NPtr = Header;
	while (num --)
	{
		TPtr = (Polynomial)malloc(sizeof(struct PolyNode));
		TPtr->link = NULL;
		scanf("%d %d", &TPtr->coef, &TPtr->expon);
		NPtr->link = TPtr;
		NPtr = TPtr;
	}
	return Header;
}

void PrintPoly(Polynomial poly)
{
	Polynomial TPtr = poly->link;
	while(TPtr != NULL)
	{
		if (TPtr->link != NULL)
			printf("%d %d ", TPtr->coef, TPtr->expon);
		else
			printf("%d %d\n", TPtr->coef, TPtr->expon);
		TPtr = TPtr->link;
	} 
}
