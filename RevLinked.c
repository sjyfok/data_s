#include <stdio.h>
#include <stdlib.h>

#define		MaxSize		(100000+1)

typedef struct LNode*  PList;

struct LNode {
	int addr;
	int data;
	int n_addr;
	PList next;
};


void ListDisp(PList list);
PList SortByAddr(PList list, int f_addr);
void ReversList(PList pList, int r_N);

int main(void)
{
	int f_addr, N, r_N;
	int i;

	PList pList, pTmp, pVal;

	scanf("%d %d %d\n", &f_addr, &N, &r_N);
	pList = (PList)malloc(sizeof(struct LNode));
	pTmp = pList;
	for(i = 0; i < N; i ++)
	{
		pVal = (PList)malloc(sizeof(struct LNode));
		scanf("%d %d %d", &pVal->addr, &pVal->data, &pVal->n_addr);
		pVal->next = NULL;
		pTmp->next = pVal;
		pTmp = pVal;		
	}
	printf("\n");
	//disp
	//ListDisp(pList);
	pList = SortByAddr(pList, f_addr);
	ReversList(pList, r_N);
	ListDisp(pList);
	return 0;
}

void ReversList(PList pList, int r_N)
{
	int i = 1;
	PList pTmp = pList->next;
	PList pGap = pList;
	PList prev = pList, pafter = NULL;
	PList pGaplast = NULL;
	if (pList->data < r_N)
		return ;
	else {
		while (pList->data+1-i >= r_N) { //i < pList->data+1) {
			while(i%r_N != 0) {
				if (prev != pGap) {
					pafter = pTmp->next;
					pTmp->next = prev;
					pTmp->n_addr = prev->addr;
				} else {
					pafter = pTmp->next;
					pTmp->next = NULL;
					pGaplast = pTmp;
				}
				prev = pTmp;
				pTmp = pafter;

				i ++;
			}

	 		pGap->next = pTmp;
			pafter = pTmp->next;
			pTmp->next = prev;
			pTmp->n_addr = prev->addr;
			pGaplast->next = pafter;
			pGaplast->n_addr = pafter->addr;
			pGap = pGaplast;
			prev = pGap;
			pTmp = pafter;
			i ++;
		}
	}
	return ;
}

void ListDisp(PList list)
{
	PList pTmp;
	pTmp = list->next;

	while(pTmp) {
		if (pTmp->addr == 0)
			printf("00000 %d ", pTmp->data);
		else 	if (pTmp->addr < 10) 
			printf("0000%d %d ", pTmp->addr, pTmp->data);
		else if (pTmp->addr < 100)
			printf("000%d %d ", pTmp->addr, pTmp->data);
		else if (pTmp->addr < 1000)
			printf("00%d %d ", pTmp->addr, pTmp->data);
		else if (pTmp->addr < 10000)
			printf("0%d %d ", pTmp->addr, pTmp->data);
		else
			printf("%d %d ", pTmp->addr, pTmp->data);
		
		if (pTmp->n_addr < 0)
			printf("%d\n", pTmp->n_addr);
		else 	if (pTmp->n_addr == 0)
			printf("00000\n");
		else if (pTmp->n_addr < 10)
			printf("0000%d\n", pTmp->n_addr);
		else if (pTmp->n_addr < 100)
			printf("000%d\n", pTmp->n_addr);
		else if (pTmp->n_addr < 1000)
			printf("00%d\n", pTmp->n_addr);
		else if (pTmp->n_addr < 10000)
			printf("0%d\n", pTmp->n_addr);
		else
			printf("%d\n", pTmp->n_addr);
		
//		printf("%d %d %d\n", pTmp->addr, pTmp->data, pTmp->n_addr);
		pTmp = pTmp->next;
	}
}


PList FindKth(PList list, int key)
{
	PList pRet;
	PList pTmp = list->next;
	PList pVal = list;

	while(pTmp) {
		if (pTmp->addr == key)
		{
			pVal->next = pTmp->next;
			return pTmp;
		}
		pVal = pTmp;
		pTmp = pTmp->next;
	}
	return NULL;
}

PList SortByAddr(PList list, int f_addr)
{
	PList pRet = (PList)malloc(sizeof(struct LNode));
	PList pAttch = pRet;
	PList pVal, pTmp;
	int fetch = f_addr;
	int nodecnt = 0;

	while (fetch >= 0)
	{
		pTmp = FindKth(list, fetch);	
		pTmp->next = NULL;
		pAttch->next = pTmp;
		fetch = pTmp->n_addr;
		pAttch = pAttch->next;
		nodecnt ++;
	}
	free(list);
	pRet->data = nodecnt;
	return pRet;
}

