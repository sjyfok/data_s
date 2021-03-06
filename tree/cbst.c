/*
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.

The right subtree of a node contains only nodes with keys greater than or equal to the node's key.

Both the left and right subtrees must also be binary search trees.

A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required that the tree must also be a CBT. You are supposed to output the level order traversal sequence of this BST.
Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (≤1000). Then N distinct non-negative integer keys are given in the next line. All the numbers in a line are separated by a space and are no greater than 2000.
Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.
Sample Input:

10
1 2 3 4 5 6 7 8 9 0

Sample Output:

6 3 8 1 5 7 9 0 2 4


*/
#include <stdio.h>
#include <stdlib.h>

#define		MaxSize		1001
/*
采用了建树的方法，但是可以不建树，可以在此基础上修改，
根据左右子树至少有个完美的二叉搜索树来确定根节点，序列由
小到大排列，就死完美二叉搜索树的中序遍历
*/
typedef int TElemType;
typedef struct TreeNode  ElemType;

typedef struct Que* PQue;
struct Que {
	ElemType *pBase;
	int head;
	int tail;
	int cap;
};

PQue QueInit(int size);
void QueDestroy(PQue QPtr);
int QueFull(PQue QPtr);
int QueEmpty(PQue QPtr);
int QueInput(PQue QPtr, ElemType elem);
int QueOutput(PQue QPtr, ElemType *elem);
int QueView(PQue QPtr, ElemType *elem);
void QueDisp(PQue QPtr);


typedef struct TreeNode *PBinTree;
struct TreeNode
{
	TElemType data;
	PBinTree left;
	PBinTree right;
};


void SortInc(TElemType inser[], int N);
void DispSort(TElemType inser[], int N);
int GetCBTDepth(int nodecnt);
int GetCBSTRCNodeCnt(int depth, int cbstnodetol);
PBinTree  BuildTree(TElemType inser[], int N);
PBinTree BuildPBSTree(TElemType inser[], int N);
void PreOrderTraversal(PBinTree  T);
void   LevelOrderTraversal(PBinTree  T, int trav[]);
int GetPBTFloorNodeCnt(int floor);
int GetPBTNodeTolDueDepth(int depth);
int cmp(const void *a, const void *b);


int main(void)
{
	int N, i, rnodecnt;
	PBinTree T;
	TElemType inser[MaxSize];
	int trav[MaxSize];
	/////////////////////////////////
	//读取测试数据
/*	FILE *fp = fopen("test.file", "r");
	fscanf(fp, "%d", &N);
//	printf("N= %d\n", N);
	for (i = 0; i < N; i ++)
		fscanf(fp, "%d", &inser[i]);  */
	/////////////////////////////////
	//读入输入序列
	scanf("%d", &N);
	for (i = 0; i < N; i ++) {
		scanf("%d", &inser[i]); 
	}
	//对输入数据进行排序
	//SortInc(inser, N);
	qsort(inser, N, sizeof(TElemType), cmp);
	//DispSort(inser, N);
	T = BuildTree(inser, N);
  LevelOrderTraversal(T, trav);
	for (i = 0; i < N-1; i ++)
		printf("%d ", trav[i]);
	printf("%d\n", trav[i]);

	return 0;
}

PBinTree  BuildTree(TElemType inser[], int N)
{
	PBinTree T = NULL;
	int depth, rem_N;
	int nodecnt;

	switch(N)
	{
		case 0:
			return T;
		case 1:
			T = (PBinTree)malloc(sizeof(struct TreeNode));
			T->data = inser[0];
			T->left = T->right = NULL;
			return T;
		case 2:
			T = (PBinTree)malloc(sizeof(struct TreeNode));
			T->data = inser[1];
			T->right = NULL;
			T->left = (PBinTree)malloc(sizeof(struct TreeNode));
			T->left->data = inser[0];
			T->left->left = T->left->right = NULL;
			return T;
		default:
			depth = GetCBTDepth(N);
			nodecnt = GetPBTNodeTolDueDepth(depth);
			if (nodecnt == N)
			{
				T = BuildPBSTree(inser, N);
			} else
			{
				int node, tmp, R_pos; //不完美的个数
				node = GetPBTNodeTolDueDepth(depth-1);
				node = N-node;
				tmp  = GetPBTFloorNodeCnt(depth-1);
				if (node == tmp)  //左右都是完美二叉树
				{
					int rnodecnt = GetPBTNodeTolDueDepth(depth-2);
					R_pos = N-rnodecnt-1;

					//建立根
					T = (PBinTree)malloc(sizeof(struct TreeNode));
					T->data = inser[R_pos];
					T->right = BuildPBSTree(&inser[R_pos+1], N-R_pos-1);
					T->left =  BuildPBSTree(inser, R_pos);

				}
				else	if (node < tmp) //右子树是完美二叉树
				{
					int rnodecnt = GetPBTNodeTolDueDepth(depth-2);//减去根节点层和最后的不满层 // GetCBSTRCNodeCnt(depth, N);
					R_pos = N-rnodecnt-1;
					//建立根
					T = (PBinTree)malloc(sizeof(struct TreeNode));
					T->data = inser[R_pos];
					T->right = BuildPBSTree(&inser[R_pos+1], N-R_pos-1);
					T->left = BuildTree(inser, R_pos);
				}
				else //左子树是完美二叉树
				{
					int lnodecnt = GetPBTNodeTolDueDepth(depth-1); //减去根节点层
					R_pos = lnodecnt;
					//建立根
					T = (PBinTree)malloc(sizeof(struct TreeNode));
					T->data = inser[R_pos];
					T->left = BuildPBSTree(inser, lnodecnt);
					T->right = BuildTree(&inser[R_pos+1], (N-lnodecnt-1));
				}
			}
			return T;
	}

	return T;	
}

//得到指定层数的节点树 完美二叉树
int GetPBTFloorNodeCnt(int floor)
{
	int ret = 1, f;

	for (f = 1; f < floor; f ++)
	{
		ret *= 2;
	}
	return ret;
}

//建立完美二叉搜索树 输入节点列表 和节点个数
PBinTree BuildPBSTree(TElemType inser[], int N)
{
	//输入
	PBinTree T = NULL;

	int r_pos = N-1;
	r_pos >>= 1; //根节点位置
	
	
	T = (PBinTree)malloc(sizeof(struct TreeNode));
	T->data = inser[r_pos];
	T->left = T->right = NULL;
	
	if (N > 1)
	{
		//建立左子树
		T->left = BuildPBSTree(inser, r_pos);
		//建立右子树
		T->right = BuildPBSTree(&inser[r_pos+1], r_pos);
	}
	return T;
}


//完美二叉树由深度获得节点个数
int GetPBTNodeTolDueDepth(int depth)
{

	if (depth > 0)
	{
		int nodecnt = 1;
		int i = 0;
		for (i = 0; i < depth; i ++)
			nodecnt *= 2;
		return (nodecnt-1);
	}
	return 0;
}

//得到完全二叉搜索数的右子树的节点个数 其右子树一定是完美二叉树
int GetCBSTRCNodeCnt(int depth, int cbstnodetol)
{
	int rdepth, i, nodecnt;
	
	//计算depth深度的完美二叉树的节点个数 判断树是否是完美二叉树
	nodecnt = GetPBTNodeTolDueDepth(depth);
	if (nodecnt == cbstnodetol)
	{
		return (cbstnodetol-1)/2;  //完美二叉树
	}
	else
	{
		rdepth = depth-2;
		nodecnt = GetPBTNodeTolDueDepth(rdepth);
		return nodecnt;
	}
}

//得到完全二叉树的深度
int GetCBTDepth(int nodecnt)
{
	int d = 0, i;
	int trynode = 1;
	if (nodecnt <= 0)
		return 0;
	while (trynode < nodecnt)
	{
		d ++;
		trynode = GetPBTNodeTolDueDepth(d);
	}
	return d;
}

void DispSort(TElemType inser[], int N)
{
	int i = 0;
	for (i = 0; i < N; i ++)
		printf("%d ", inser[i]);
	printf("\n");
}

int cmp(const void *a, const void *b)
{
	int *pa = (int*)a;
	int *pb = (int*)b;
	return *pa-*pb;
}

void SortInc(TElemType inser[], int N)
{
	int i, j;
	TElemType tmp;

	for (i = 0; i < N; i ++)
	{
		tmp = inser[i];
		for (j = i+1; j < N; j ++)
		{
			if (tmp > inser[j])
			{
				tmp = inser[j];
				inser[j] = inser[i];
			}
		}
		inser[i] = tmp;
	}
}



//先序遍历树
void PreOrderTraversal(PBinTree  T)
{
	if (T != NULL)
	{
		printf("%d ", T->data);
		PreOrderTraversal(T->left);
		PreOrderTraversal(T->right);
	}
}


//层次遍历
void   LevelOrderTraversal(PBinTree  T , int trav[])
{
	PQue que;
	int i = 0;
	struct TreeNode  TN;
	que = QueInit(MaxSize);
	if (T != NULL) {
		QueInput(que, *T);
		while (!QueEmpty(que)) {
			QueOutput(que, &TN);
			//printf("%d ", TN.data);
			trav[i++] = TN.data;
			if (TN.left != NULL)
				QueInput(que, *(TN.left));
			if (TN.right != NULL)
				QueInput(que, *(TN.right));
		}
	}
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
		printf("%d ", QPtr->pBase[i].data);
		i ++;
		i %= QPtr->cap;
	}
	printf("\n");
}
