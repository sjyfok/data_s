#include <stdio.h>
#include <stdlib.h>

/*完全二叉搜索树的中序遍历就是从小到大有序的序列，因此排序得到中序遍历
完全二叉搜索树的右子树一定是完美二叉树，从而得到右子树的节点个数，也就得到了
根节点的位置，得到根节点后，就可以建立树，再做层次遍历。
*/
#define		MaxSize		1000

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


/*PAVLTree  BuiltAVLTree(TElemType inser[], int N);
void PreOrderTraversal(PAVLTree  T);
int InsertAVL(PAVLTree *T, TElemType e, int *taller);
void LeftBalance(PAVLTree *T);
void RightBalance(PAVLTree *T);
void R_Rotate(PAVLTree *T);
void L_Rotate(PAVLTree *T);
*/
void SortInc(TElemType inser[], int N);
void DispSort(TElemType inser[], int N);
int GetCBTDepth(int nodecnt);
int GetCBSTRCNodeCnt(int depth, int cbstnodetol);
PBinTree  BuildTree(TElemType inser[], int S,  int E, int R_pos);
PBinTree BuildPBSTree(TElemType inser[], int N);
void PreOrderTraversal(PBinTree  T);
void   LevelOrderTraversal(PBinTree  T,  int trav[]);

int main(void)
{
	int N, i, rnodecnt;
	TElemType inser[MaxSize];
	int depth, R;
	PBinTree T;

	//读入输入序列
	scanf("%d", &N);
	for (i = 0; i < N; i ++) {
		scanf("%d", &inser[i]); 
	}
	//对输入数据进行排序
	SortInc(inser, N);
	DispSort(inser, N);
	depth = GetCBTDepth(N); //获得完全二叉树深度
	printf("D=%d\n", depth);
	rnodecnt = GetCBSTRCNodeCnt(depth, N);
	printf("RC=%d\n", rnodecnt);
	//建立树 由根节点位置和一个中序遍历序列
	R = N-rnodecnt-1;
	printf("R = %d: %d\n", R, inser[R]);
	T = BuildTree(inser, N, R);
	//T = BuildPBSTree(inser, N);
	PreOrderTraversal(T);
//	if (T)
//		printf("%d\n", T->data);
	return 0;
}

PBinTree  BuildTree(TElemType inser[], int N)
{
	PBinTree T = NULL;
	int depth, rem_N;

	rem_N = N;
	while (rem_N > 0)
	{
		depth = GetCBTDepth(rem_N);
		nodecnt =  GetPBTNodeTolDueDepth(depth);
		if (nodecnt == rem_N)  //完美二叉搜索树
		{
			if (T == NULL)
				T = BuildPBSTree(inser, rem_N);
			else
				T->left = BuildPBSTree(inser, rem_N);
			break;
		}
		else
		{
				rnodecnt = GetCBSTRCNodeCnt(depth, rem_N);
				R_pos = rem_N-rnodecnt-1;
		
				//建立根
				T = (PBinTree)malloc(sizeof(struct TreeNode));
				T->data = inser[R_pos];
				T->left = T->right = NULL;
				//右子树已经是完美二叉搜索树
				T->right = BuildPBSTree(&inser[R_pos+1], rem_N-R_pos-1);
				rem_N = R_Pos;
		}		
	}
	return T;	
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
void   LevelOrderTraversal(PBinTree  T,  int trav[])
{
	PQue que;
	int i = 0;
	struct TreeNode  TN;
	que = QueInit(MaxSize);
	if (T != NULL) {
		QueInput(que, *T);
		while (!QueEmpty(que)) {
			QueOutput(que, &TN);
			printf("%d ", TN.data);

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
