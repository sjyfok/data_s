/*
设计函数分别求两个一元多项式的乘积与和。
输入格式:

输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。
输出格式:

输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。
输入样例:

4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1

输出样例:

15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0


*/
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
	PrintPoly(M);
	PrintPoly(S);
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
	while (APtr != NULL)
	{
		//ai×(b0-bn)
		MHPtr = (Polynomial)malloc(sizeof(struct PolyNode));
		MPtr = MHPtr;
		
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
	//		PrintPoly(SPtr);
	//		PrintPoly(MHPtr);
			SPtr = SumOfPoly(TMPPtr, MHPtr);
	//		PrintPoly(SPtr);
			//realse MPtr
			MPtr = MHPtr->link;
			while(MPtr)
			{
				TMPPtr = MPtr->link;		
				free(MPtr);
				MPtr = TMPPtr;
			}
			free(MHPtr);
			//MHPtr->link = NULL;
			//MPtr = MHPtr;
		} 
		else
		{
			SPtr = MHPtr;
			//PrintPoly(SPtr);
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
			if (TPtr->coef == 0)
			{
				free(TPtr);
				continue;
			}
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
	while (num)
	{
		TPtr = (Polynomial)malloc(sizeof(struct PolyNode));
		TPtr->link = NULL;
		scanf("%d %d", &TPtr->coef, &TPtr->expon);
		if (!TPtr->coef)
		{
			free(TPtr);
			continue;
		}
		NPtr->link = TPtr;
		NPtr = TPtr;
		num --;
	}
	return Header;
}

void PrintPoly(Polynomial poly)
{
	Polynomial TPtr = poly->link;
	if (TPtr == NULL)	{
		printf("%d %d\n", 0, 0);
	}
	else {
		while(TPtr != NULL)
		{
			if (TPtr->link != NULL)
				printf("%d %d ", TPtr->coef, TPtr->expon);
			else
				printf("%d %d\n", TPtr->coef, TPtr->expon);
			TPtr = TPtr->link;
		} 
	}
}
