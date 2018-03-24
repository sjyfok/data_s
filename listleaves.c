#include <stdio.h>
#include <stdlib.h>

#define	MaxTree 10

typedef  char	 ElemType;
typedef  int	Tree;
typedef  Tree QElemType;
#define	Null -1

//队列
typedef struct Que* PQue;
struct Que {
	QElemType *pBase;
	int head;
	int tail;
	int cap;
};


PQue QueInit(int size);
void QueDestroy(PQue QPtr);
int QueFull(PQue QPtr);
int QueEmpty(PQue QPtr);
int QueInput(PQue QPtr, QElemType elem);
int QueOutput(PQue QPtr, QElemType *elem);
int QueView(PQue QPtr, QElemType *elem);
void QueDisp(PQue QPtr);


//end 队列


struct TreeNode
{
	ElemType elem;

	Tree left;
	Tree right;
};
struct TreeNode T1[MaxTree], T2[MaxTree];

int BuiltTree(struct TreeNode T[]);
void PreOrderTraversal(struct TreeNode T[], Tree R);
int  LevelOrderTraversal(struct TreeNode T[], Tree R, int trav[]);
int Isomorphic(Tree R1, Tree R2);

int main(void)
{
	Tree R1, R2;
	int array[MaxTree], len, i;
	R1 = BuiltTree(T1);
//	R2 = BuiltTree(T2);
//	PreOrderTraversal(T1, R1);
	len = LevelOrderTraversal(T1, R1, array);
	for (i = 0; i < len-1; i ++)
		printf("%d ", array[i]);
	printf("%d\n", array[i]);
//	printf("\n");
//	PreOrderTraversal(T2, R2);
//	printf("\n");
/*	if (Isomorphic(R1, R2))
		printf("Yes\n");
	else
		printf("No\n");*/
	return 0;
}

int BuiltTree(struct TreeNode T[])
{
	int N, i;
	Tree R = 0;
	int Check[MaxTree];
	ElemType  cl, cr;
	scanf("%d", &N);
	if (N <= 0)
		return Null;
	//printf("%d\n", N);
	//确认根节点的位置

	for(i = 0; i < N; i ++)
		Check[i] = 0;

	for(i = 0; i < N; i ++)
	{
		ElemType c;

	//	scanf("%c ", &c);
	//	while(c == '\n' || c == ' ') scanf("%c", &c);
		T[i].elem = 'A'+i;
		scanf("%c ", &c);
		while(c == '\n' || c == ' ') scanf("%c", &c);
		cl = c;
		scanf("%c ", &c);
		while(c == '\n' || c == ' ') scanf("%c", &c);
		cr = c;

//		while(scanf("%c %c %c\n", &T[i].elem,&cl,&cr);
		//printf("%c %c %c\n", T[i].elem, cl, cr);
		if (cl != '-') {
			T[i].left = cl-0x30;
			Check[T[i].left] = 1;
		}
		else T[i].left = Null;
		
		if (cr != '-') {
			T[i].right = cr-0x30;
			Check[T[i].right] = 1;
		}
		else T[i].right = Null; 
	}

	for(i = 0; i < N; i ++)
	{
		if (Check[i] == 0)
			R = i;
	}
	/*for (i = 0; i < N; i ++)
	{
		printf("%c %d %d\n", T[i].elem, T[i].left, T[i].right);
	}*/
	return R;
}

//先序遍历树
void PreOrderTraversal(struct TreeNode T[], Tree R)
{
	//printf("R= %d", R);
	if (R != Null)
	{
		//printf("%c", T[R].elem);
		if (T[R].left == Null && T[R].right == Null)
			printf("%d", R);
		PreOrderTraversal(T, T[R].left);
		PreOrderTraversal(T, T[R].right);
	}
}

//层次遍历
int  LevelOrderTraversal(struct TreeNode T[], Tree R, int trav[])
{
	PQue que;
	Tree TN;
	int i = 0;
	que = QueInit(MaxTree);
	if (R != Null) {
		QueInput(que, R);
		while (!QueEmpty(que)) {
			QueOutput(que, &TN);
			if((T[TN].left == Null) && (T[TN].right == Null))
				trav[i ++] = TN;
				//printf("%d", TN);
			if (T[TN].left != Null)
				QueInput(que, T[TN].left);
			if (T[TN].right != Null)
				QueInput(que, T[TN].right);
		}
	}
	return i;	
}

/*
int Isomorphic(Tree R1, Tree R2)
{
	if ((R1 == Null) && (R2 == Null))
		return 1;
	if (((R1 == Null)&&(R2!= Null)) || ((R1 != Null)&&(R2 == Null)))
		return 0;
	if ((T1[R1].left == Null) && (T2[R2].left == Null) && (T1[R1].right = Null) &&
		(T2[R2].right == Null) && (T1[R1].elem != T2[R2].elem))
		return 0;
	if ((T1[R1].left == Null) && (T2[R2].left == Null))
		return Isomorphic(T1[R1].right, T2[R2].right);
	if (((T1[R1].left != Null)&&(T2[R2].left != Null)) &&
		((T1[T1[R1].left].elem) == (T2[T2[R2].left].elem)))
			return (Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right));
	else
		return (Isomorphic(T1[R1].left, T2[R2].right) && Isomorphic(T1[R1].right, T2[R2].left));
}
*/

//队列
PQue QueInit(int size)
{
	PQue QPtr = (PQue)malloc(sizeof(struct Que)); 

	QPtr->pBase = (QElemType*)malloc(sizeof(QElemType)*size);
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

int QueInput(PQue QPtr, QElemType elem)
{
	if (QueFull(QPtr))
		return 0;
	QPtr->pBase[QPtr->tail ++] = elem;
	QPtr->tail %= QPtr->cap;
	return 1;
}

int QueOutput(PQue QPtr, QElemType *elem)
{
	if (QueEmpty(QPtr))
		return 0;
	*elem = QPtr->pBase[QPtr->head ++];
	QPtr->head %= QPtr->cap;
	return 1;
}

int QueView(PQue QPtr, QElemType *elem)
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
