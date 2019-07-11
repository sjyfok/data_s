/*
We have a network of computers and a list of bi-directional connections. Each of these connections allows a file transfer from one computer to another. Is it possible to send a file from any computer on the network to any other?
Input Specification:

Each input file contains one test case. For each test case, the first line contains N (2≤N≤10​4​​), the total number of computers in a network. Each computer in the network is then represented by a positive integer between 1 and N. Then in the following lines, the input is given in the format:

I c1 c2  

where I stands for inputting a connection between c1 and c2; or

C c1 c2    

where C stands for checking if it is possible to transfer files between c1 and c2; or

S

where S stands for stopping this case.
Output Specification:

For each C case, print in one line the word "yes" or "no" if it is possible or impossible to transfer files between c1 and c2, respectively. At the end of each case, print in one line "The network is connected." if there is a path between any pair of computers; or "There are k components." where k is the number of connected components in this network.
Sample Input 1:

5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S

Sample Output 1:

no
no
yes
There are 2 components.

Sample Input 2:

5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
I 1 3
C 1 5
S

Sample Output 2:

no
no
yes
yes
The network is connected.
*/
#include <stdio.h>
#include <stdlib.h>

#define		MAXN		10000

typedef int ElemType;

typedef int SetName;
typedef ElemType SetType[MAXN];

void Initialization(SetType S, int nCount);
void DispSetType(SetType S, int nCount);
void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S, int nCount);

int main(void)
{
    SetType S;

    int N;
    char in;

	/////////////////////////////////
	//读取测试数据
/*	FILE *fp = fopen("test.file", "r");
	fscanf(fp, "%d %d", &N, &M);
	printf("N= %d M= %d\n", N, M);
    */
    scanf("%d\n", &N);
    
    Initialization(S, N);

    do {
        scanf("%c", &in);
        switch(in)
        {
            case 'I':
                Input_connection(S);
                break;
            case 'C':
                Check_connection(S);
                break;
            case 'S':
                Check_network(S, N);
                break;
            default: break;
        }
    } while (in != 'S');
    return 0;
}

SetName Find(SetType S, ElemType x)
{
    for (; S[x] >= 0; x=S[x]);
    return x;
}

//按规模合并
void Union(SetType S, SetName Root1, SetName Root2)
{
    if(S[Root1] < S[Root2])
    {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
    else
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;    
    }
}

void Check_network(SetType S, int nCount)
{
    int rootCnt = 0;

    for(int i = 0; i < nCount; i ++)
    {
        if(S[i] < 0)
            rootCnt ++;
    }
    if(rootCnt == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", rootCnt);
}

void Input_connection(SetType S)
{
    ElemType e, v;
    SetName Root1, Root2;

    scanf("%d %d\n", &e, &v);
    Root1 = Find(S, e-1);
    Root2 = Find(S, v-1);
    if(Root1 != Root2)
        Union(S, Root1, Root2);
}   

void Check_connection(SetType S)
{
    ElemType e, v;
    SetName Root1, Root2;
    scanf("%d %d\n", &e, &v);
    Root1 = Find(S, e-1);
    Root2 = Find(S, v-1);
    if(Root1 != Root2)
        printf("no\n");
    else
        printf("yes\n");
}

void Initialization(SetType S, int nCount)
{
    for(int i = 0; i < nCount; i ++)
    {
        S[i] = -1;
    }
}

void DispSetType(SetType S, int nCount)
{
    for(int i = 0; i < nCount; i ++)
        printf("%d ", S[i]);
    printf("\n");
}
