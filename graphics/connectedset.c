/*
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。
输入格式:

输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。
输出格式:

按照"{ v​1​​ v​2​​ ... v​k​​ }"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。
输入样例:

8 6
0 7
0 1
2 0
4 1
2 4
3 5

输出样例:

{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }


*/

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 10

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct ENode *PtrToENode;
struct ENode
{
	Vertex V1, V2;
//	WeightType Weight;
};
typedef PtrToENode Edge;

typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;
	int Ne;
	int *visit;
	WeightType G[MaxVertexNum][MaxVertexNum];
	//DataType Data[MaxVertexNum];
};

typedef PtrToGNode MGraph;

typedef  Vertex ElemType;
typedef struct Que* Queue;
struct Que {
	ElemType *pBase;
	int head;
	int tail;
	int cap;
};

Queue QueInit(int size);
void QueDestroy(Queue QPtr);
int QueFull(Queue QPtr);
int QueEmpty(Queue QPtr);
int QueInput(Queue QPtr, ElemType elem);
int QueOutput(Queue QPtr, ElemType *elem);
//int QueView(PQue QPtr, ElemType *elem);
//void QueDisp(PQue QPtr);


MGraph CreateGraph(int VertexNum)
{
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->visit = (int)malloc(sizeof(int)*VertexNum);
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0; V < Graph->Nv; V++)
	{
		for (W = 0; W < Graph->Nv; W++)
		{
			Graph->G[V][W] = 0;
		}

		Graph->visit[V] = 0; //初始化visit数组 方便变量
	}


	return Graph;
}

void InitVisit(MGraph Graph)
{
	for (Vertex V = 0; V < Graph->Nv; V++)
	{
		Graph->visit[V] = 0;
	}
}

void InsertEdge(MGraph Graph, Edge E)
{
	Graph->G[E->V1][E->V2] = 1;// = E->Weight;
	Graph->G[E->V2][E->V1] = 1; // E->Weight;
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0)
	{
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i < Graph->Ne; i++)
		{
			//scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			scanf("%d %d", &E->V1, &E->V2);
			InsertEdge(Graph, E);
		}
		free(E);
	}

	/*for (V = 0; V  < Graph->Nv; V ++)
	{
		scanf("%c", &(Grap))
	}*/
	return Graph;
}

void Visit(Vertex V)
{
	printf("%d ", V);
//	fflush(stdout);
}

void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex))
{
	if (Graph->visit[V] == 0)
	{
		Visit(V);
		Graph->visit[V] = 1;
		for (Vertex w = 0; w < Graph->Nv; w++)
		{
			if (Graph->G[V][w])
			{
				if (Graph->visit[w] != 1)
				{
					DFS(Graph, w, Visit);
				}
			}
		}
	}
}

int IsEdge(MGraph Graph, Vertex V, Vertex W)
{
	if (Graph->G[V][W] == 1)
	{
		return 1;
	}
	return 0;
}

void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex))
{
	Queue Q;
	Vertex V, W;

	Q = QueInit(Graph->Nv);
	Visit(S);
	Graph->visit[S] = 1;
	QueInput(Q, S);
	while (!QueEmpty(Q))
	{
		QueOutput(Q, &V);
		for(W = 0; W < Graph->Nv; W ++)
			if (!Graph->visit[W] && IsEdge(Graph, V, W))
			{
				Visit(W);
				Graph->visit[W] = 1;
				QueInput(Q, W);
			}
	}

}

int main()
{
	int i;
	MGraph Graph;

	/*scanf("%d", &N);
	Graph = CreateGraph(N);*/
	Graph = BuildGraph();
	InitVisit(Graph);
	i = 0; 
	while (i < Graph->Nv)
	{
		if (Graph->visit[i] != 1)
		{
			printf("{ ");
			DFS(Graph, i, Visit);
			printf("}\n");
		}
		i++;
	}
	
	InitVisit(Graph);

	i = 0;
	while (i < Graph->Nv)
	{
		if (Graph->visit[i] != 1)
		{
			printf("{ ");
			BFS(Graph, i, Visit);
			printf("}\n");
		}
		i++;
	}

	fflush(stdout);
    return 0;
}


//队列
Queue QueInit(int size)
{
	Queue QPtr = (Queue)malloc(sizeof(struct Que));

	QPtr->pBase = (ElemType*)malloc(sizeof(ElemType)*size);
	QPtr->cap = size;
	QPtr->head = QPtr->tail = 0;
	return QPtr;
}

int QueInput(Queue QPtr, ElemType elem)
{
	if (QueFull(QPtr))
		return 0;
	QPtr->pBase[QPtr->tail++] = elem;
	QPtr->tail %= QPtr->cap;
	return 1;
}


int QueFull(Queue QPtr)
{
	if ((QPtr->tail + 1) % QPtr->cap == QPtr->head)
		return 1;
	return 0;
}

int QueEmpty(Queue QPtr)
{
	if (QPtr->tail == QPtr->head)
		return 1;
	return 0;
}

int QueOutput(Queue QPtr, ElemType *elem)
{
	if (QueEmpty(QPtr))
		return 0;
	*elem = QPtr->pBase[QPtr->head++];
	QPtr->head %= QPtr->cap;
	return 1;
}

void QueDestroy(Queue QPtr)
{
	free(QPtr->pBase);
	free(QPtr);
}
