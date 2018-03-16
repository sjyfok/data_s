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
	pque = QueInit(PushCnt);

	for (i = 0; i < CheckCnt; i ++) {
		for (j = 0; j < PushCnt; j ++) {
			QueInput(pque, pArray[i*PushCnt+j]);
		}
		if (PushSeqCheck(pstk, pque, pArray+i*PushCnt, PushCnt))
		{
			printf("YES\n");
		}
		else
			printf("NO\n");
	}
}

int PushSeqCheck(PStk pstk, PQue pque, int *pBuf, int Bufsize)
{
	int i = 0;
	int elem, tmp;
	for (i = 0; i < Bufsize; i ++) {
		elem = pBuf[i];
		if (QueView(pque, &tmp)) {
			if (tmp != elem) { //不是队头
				if (StackView(pstk, &tmp)) {
					if (tmp != elem)  //不是栈顶
						return 0; //序列不能产生
					else {
						
					}
				} else
					return 0;
			} else {
				if (StackFull(pstk)) //是队头如果栈满
					return 0;
			}
		}
	}
	return 1;
}

//栈
PStack  InitStack(int size)
{
	PStack *pStk;
	pStk->pBase = (ElemType*)malloc(sizeof(ElemType)*size);
	pStk->i_sp = 0;
	pStk->cap = size;
	return pStk;
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
	if (StackEmpty(pstk)
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
//队列
PQue QueInit(int size)
{
	PQue QPtr;
	
	QPtr->pBase = (ElemType*)malloc(sizeof(ElemType)*size);
	QPtr->cap = size;
	QPtr->head = QPtr->tail = 0;
	return QPtr;
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
