#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

//还有问题，采用BFS算法解题，用例通过情况57/59，不知道最后两个用例为什么不通过(无意中找到，队列空间太小导致打印T的地方比较多)；后面有机会再调试；
//当前先主要熟悉编程思想和锻炼动手能力
char A0[]={'X','X','X','X'};
char A1[]={'X','O','O','X'};
char A2[]={'O','X','O','X'};
char A3[]={'X','O','X','X'};
char *A[]={A0,A1,A2,A3};
int B[]={4,4,4,4};

int *father=NULL;
int RowSize=0;
int ColSize=0;
#define QMAX 10000
int Q[QMAX]={0};
int wr=0;
int rd=0;
int QSize=0;
void solve(char** board, int boardSize, int* boardColSize);

int enqueue(int cnt)
{
    if (QSize==QMAX) {
        printf("TTTTTTTTTTTTTT");
        return -1;
    }
    Q[wr]=cnt;
    QSize++;
    wr=(wr+1)%QMAX;    
    return 0;
}

int dequeue(void)
{
    int tmp=0;
    if (QSize==0) {
        printf("TTTTTTTTTTTTTT");
        return -1;
    }
    tmp=Q[rd];
    QSize--;
    rd=(rd+1)%QMAX;
    return tmp;
}

int queueEmpty(void)
{
    return (QSize==0);    
}

void PrintMatrix(char** board,int boardSize,int* boardColSize)
{
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardColSize[i]; j++)
        {
            printf("%c",board[i][j]);
            if (j<boardColSize[i]-1) {
                printf(" ");
            }
        }
        printf("\n");        
    }
    return;
}


int main()
{
    int result = 0;

    PrintMatrix(A, sizeof(A)/sizeof(A[0]), B);
    printf("************************\n");
    solve(A, sizeof(A)/sizeof(A[0]), B);
    PrintMatrix(A, sizeof(A)/sizeof(A[0]), B);

    return 0;
}

void doing(char ** board,int cnt)
{
    int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};    

    enqueue(cnt);
    while(!queueEmpty())
    {
        int tmpcnt=dequeue();
        int row=tmpcnt/ColSize;
        int col=tmpcnt%ColSize;
        board[row][col]='L';
        //遍历周边的节点
        for(int i = 0; i < 4; i++)
        {
            int tmpRow=row+dir[i][0];
            int tmpCol=col+dir[i][1];
            if (tmpRow<0 || tmpRow>=RowSize || tmpCol<0 || tmpCol>=ColSize) {
                continue;
            }       
            if(board[tmpRow][tmpCol] == 'L') continue;        
            if(board[tmpRow][tmpCol] == 'O') enqueue(tmpRow*ColSize+tmpCol);
        }  
    }
    
    return;
}

void solve(char** board, int boardSize, int* boardColSize){
    if(board==NULL || boardSize==0 || boardColSize==NULL)
    {
        return;
    }
    RowSize = boardSize;
    ColSize = boardColSize[0];

    //从4条边界出发对所有连通的点进行处理，先列再行
    for(int i = 0; i < RowSize; i++)
    {
        if (board[i][0]=='O') {
            doing(board,i*ColSize);
        }
        if (board[i][ColSize-1]=='O') {
            doing(board,i*ColSize+ColSize-1);
        }
    }

    for(int i = 0; i < ColSize; i++)
    {
        if (board[0][i]=='O') {
            doing(board,i);
        }
        if (board[RowSize-1][i]=='O') {
            doing(board,(RowSize-1)*ColSize+i);
        }       
    }    
#if 1
    for(int i = 0; i < RowSize; i++)
    {
        for(int j = 0; j < ColSize; j++)
        {
            if (board[i][j]=='O') {
                board[i][j]='X';
            }
            if (board[i][j]=='L') {
                board[i][j]='O';
            }           
        }        
    }
#endif    
    return;
}


#if 0 //并查集顾名思义需要两个函数：查找和合并；相比BFS空间占用比较少，最多数组的一倍
int Find(int a)
{
    int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
    int row=a/boardColSize;
    int col=a%boardColSize;

    for(int i = 0; i < 4; i++)
    {
        int tmpRow=row+dir[i][0];
        int tmpCol=col+dir[i][1];
        if(board[tmpRow][tmpCol] == 'O') return (tmpRow*boardColSize+tmpCol);
    }
    
    return -1;
}

int Father(int a)
{
    int tmp=a;
    while(tmp!=father[tmp]){//循环找到最root节点
        tmp=father[tmp];
    }

    return tmp;

    father = (int*)malloc(sizeof(int)*count);
    for(int i = 0; i < count; i++)
    {
        father[i]=i;
    }
    

    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardColSize[i]; j++)
        {
            Father(i*boardColSize[i]+j);
        }
        
    }
}


//并查集参考：之前思路理解，但细节点理解不深入，导致没有串接起来
class UnionFind {
    int [] parents;
    public UnionFind(int totalNodes) {
        parents = new int[totalNodes];
        for(int i = 0; i < totalNodes; i++) {
            parents[i] = i;
        }
    }
    
    void union(int node1, int node2) {
        int root1 = find(node1);
        int root2 = find(node2);
        if(root1 != root2) {
            parents[root2] = root1;
        }
    }
    
    int find(int node) {
        while(parents[node] != node) {
            parents[node] = parents[parents[node]];
            node = parents[node];
        }
        return node;
    }
    
    boolean isConnected(int node1, int node2) {
        return find(node1) == find(node2);
    }


作者：windliang
链接：https://leetcode-cn.com/problems/surrounded-regions/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-3-6/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#endif
