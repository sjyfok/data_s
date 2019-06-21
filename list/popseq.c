/*
Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.
Input Specification:

Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.
Output Specification:

For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.
Sample Input:

5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2

Sample Output:

YES
NO
NO
YES
NO


*/
#include <stdio.h>
#include <stdlib.h>

#define		MaxSize		1000

typedef int ElemType;
typedef struct Stack*  PStack;

struct Stack {
	ElemType *pBase;
	int i_sp;
	int cap;
};

typedef struct Que* PQue;
struct Que {
	ElemType *pBase;
	int head;
	int tail;
	int cap;
};

PStack  InitStack(int size);
void StackDestroy(PStack pstk);
int StackFull(PStack pstk);
int StackEmpty(PStack pstk);
int StackPush(PStack pstk, ElemType elem);
int StackPop(PStack pstk, ElemType *elem);
int StackView(PStack pstk, ElemType *elem);
void StackDisp(PStack pstk);


PQue QueInit(int size);
void QueDestroy(PQue QPtr);
int QueFull(PQue QPtr);
int QueEmpty(PQue QPtr);
int QueInput(PQue QPtr, ElemType elem);
int QueOutput(PQue QPtr, ElemType *elem);
int QueView(PQue QPtr, ElemType *elem);
void QueDisp(PQue QPtr);

int PushSeqCheck(PStack pstk, PQue pque, int *pBuf, int Bufsize);
int main(void)
{
	int StackCap, PushCnt, CheckCnt;
	int *pArray;
	int i = 0, j = 0;
	PStack pstk;
	PQue pque;

	scanf("%d %d %d", &StackCap, &PushCnt, &CheckCnt);
	//printf("%d %d %d\n", StackCap, PushSeq, CheckCnt);
	pArray = (int*)malloc(sizeof(int)*PushCnt*CheckCnt);
	
	for (i = 0; i < CheckCnt; i ++) {
		for (j = 0; j < PushCnt; j ++) {
			scanf("%d", &pArray[i*PushCnt+j]);
		}
	}
	
	//disp
	/*for (i = 0; i < CheckCnt; i ++) {
		for (j = 0; j < PushSeq; j ++) {
			printf("%d ", pArray[i*PushSeq+j]);
		}
		printf("\n");
	}*/	
	pstk = InitStack(StackCap);
	pque = QueInit(PushCnt+1);

	for (i = 0; i < CheckCnt; i ++) {
		pstk = InitStack(StackCap);
		pque = QueInit(PushCnt+1);

		for (j = 0; j < PushCnt; j ++) {
//			printf("j = %d %d ", j, pArray[i*PushCnt+j]);
			QueInput(pque, j+1);
		}
		//QueDisp(pque);
		if (PushSeqCheck(pstk, pque, pArray+i*PushCnt, PushCnt))
		{
			printf("YES\n");
		}
		else
			printf("NO\n");
		QueDestroy(pque);
		StackDestroy(pstk);
	}
}

int PushSeqCheck(PStack pstk, PQue pque, int *pBuf, int Bufsize)
{
	int i = 0, ret = 0;
	int elem, tmp;
//	printf("bufsize = %d\n", Bufsize);
	while(i < Bufsize) {
		elem = pBuf[i];
//		printf("%d ", elem);
		if (QueView(pque, &tmp)) {
			if (tmp != elem) { //不是队头
				ret = StackView(pstk, &tmp);
				if (ret == 0 || tmp != elem) {
					QueOutput(pque, &tmp);
					if (!StackPush(pstk, tmp))
						return 0;
					//QueDisp(pque);
					//StackDisp(pstk);
				} else if (tmp == elem) {
					StackPop(pstk, &tmp);
					//StackDisp(pstk);
					i ++;
				}
			}
			else { //是队头
				if (StackFull(pstk))
					return 0;
				else {
					QueOutput(pque, &tmp);
					//QueDisp(pque);
					i ++;
				}
			}
		}
		else { //队已经空
			if (!StackView(pstk, &tmp))
				return 0;
			else if (tmp != elem)
				return 0;
			else {
				StackPop(pstk, &tmp);
				//StackDisp(pstk);
				i ++;
			}
		}
	}
	return 1;
}

//栈
PStack  InitStack(int size)
{
	PStack pStk = (PStack)malloc(sizeof(struct Stack));
	pStk->pBase = (ElemType*)malloc(sizeof(ElemType)*size);
	pStk->i_sp = 0;
	pStk->cap = size;
	return pStk;
}

void StackDestroy(PStack pstk)
{
	free(pstk->pBase);
	free(pstk);
}

int StackFull(PStack pstk)
{
	if (pstk->i_sp >= pstk->cap)
		return 1;
	return 0;
}

int StackEmpty(PStack pstk)
{
	if (pstk->i_sp == 0)
		return 1;
	return 0;
}

int  StackPush(PStack pstk, ElemType elem)
{
	if (StackFull(pstk))
		return 0;
	pstk->pBase[pstk->i_sp ++] = elem;
	return 1;
}

int StackPop(PStack pstk, ElemType *elem)
{
	if (StackEmpty(pstk))
		return 0;
	*elem = pstk->pBase[--pstk->i_sp];
	return 1;
}

int StackView(PStack pstk, ElemType *elem)
{
	if (StackEmpty(pstk))
		return 0;
	*elem = pstk->pBase[pstk->i_sp-1];
	return 1;
}

void StackDisp(PStack pstk)
{
	int i = 0;
	printf("Stack: ");
	while (i < pstk->i_sp) {
		printf("%d ", pstk->pBase[i]);
		i ++;
	}
	printf("\n");
}


//队列
PQue QueInit(int size)
{
	PQue QPtr = (PQue)malloc(sizeof(struct Que)); 

	QPtr->pBase = (ElemType*)malloc(sizeof(ElemType)*size);
	QPtr->cap = size;
	QPtr->head = QPtr->tail = 0;
	return QPtr;
}

void QueDestroy(PQue QPtr)
{
	free(QPtr->pBase);
	free(QPtr);
}

int QueFull(PQue QPtr)
{
	if ((QPtr->tail+1)%QPtr->cap == QPtr->head)
		return 1;
	return 0;
}

int QueEmpty(PQue QPtr)
{
	if (QPtr->tail == QPtr->head)
		return 1;
	return 0;
}

int QueInput(PQue QPtr, ElemType elem)
{
	if (QueFull(QPtr))
		return 0;
	QPtr->pBase[QPtr->tail ++] = elem;
	QPtr->tail %= QPtr->cap;
	return 1;
}

int QueOutput(PQue QPtr, ElemType *elem)
{
	if (QueEmpty(QPtr))
		return 0;
	*elem = QPtr->pBase[QPtr->head ++];
	QPtr->head %= QPtr->cap;
	return 1;
}

int QueView(PQue QPtr, ElemType *elem)
{
	if (QueEmpty(QPtr))
		return 0;
	*elem = QPtr->pBase[QPtr->head];
	return 1;
}

void QueDisp(PQue QPtr)
{
	int i;
	printf("Que: ");
	i = QPtr->head;
	while(i != QPtr->tail) {
		printf("%d ", QPtr->pBase[i]);
		i ++;
		i %= QPtr->cap;
	}
	printf("\n");
}
