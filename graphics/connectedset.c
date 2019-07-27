/*
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

int main()
{
	int N;
	MGraph Graph;

	/*scanf("%d", &N);
	Graph = CreateGraph(N);*/
	Graph = BuildGraph();
	InitVisit(Graph);
	DFS(Graph, 0, Visit);
	fflush(stdout);
    return 0;
}

