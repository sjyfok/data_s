 #include <stdio.h>
 #include <stdlib.h>

 #define	MAXSIZE	10
 #define	NotFound 0


typedef int ElementType;
typedef int Position;


struct LNode {
	ElementType Data[MAXSIZE];
	Position Last;
};

typedef struct LNode *List;

List ReadInput(void);
Position BinarySearch(List L, ElementType X);

int main(void)
{
	List L;
	ElementType X;
	Position P;

	L = ReadInput();
	scanf("%d", &X);
	P = BinarySearch(L, X);
	printf("%d\n", P);

	return 0;
}

List ReadInput(void)
{
	List L;
	int num, i;

	L = (List)malloc(sizeof(struct LNode));
	scanf("%d\n", &num);
	for (i = 1; i < num+1; i ++) {
		scanf("%d ", &L->Data[i]);
	}
	L->Last = num;
}

Position BinarySearch(List L, ElementType X)
{
	Position pi = 0;
	Position lo = 1;
	Position hi = L->Last;
	
	while(lo <= hi)
	{
		pi = lo+hi;
		pi /= 2;
		if (L->Data[pi] == X)	{
			return pi;
		}	else if (L->Data[pi] < X)		{
			lo = pi+1;
		} else {
			hi = pi-1;
		}
	}
 	return 0;
}
