#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/*
 * 小伟出发去L远的地方，汽车自带油量P，途中有N个加油站，每个加油站距离终点Ai，能加的油量为Bi，请问能否顺利到达目的地
 * 每单位距离耗油量为1个单位，如果可以达到输出最少加多少次油
 */

/* 这道题最好的方式是采用优先级队列，优先加油量大的加油站，可以使用list实现优先级队列；从高到低排列加油站 */
int N=0;
int L=0;
int P=0;
int main(void)
{
    scanf("%d",&N);
    int *A=(int *)malloc(N*sizeof(int));
    int *B=(int *)malloc(N*sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d",&A[i],&B[i]);
    }
    scanf("%d %d",&L,&P);

    for (int i = 0; i < N; i++)
    {
        if (L-A[i]>P)
        {
            continue;
        }
        enqueue(B[i]);
    }
    int cnt=0;
    int sum=P;
    while (!queueEmpty())
    {
        if (sum>=L)
        {
            return cnt;
        }
        while (sum>L-A[i])//问题的难点在于如何将高油量的先加入;一种方式是采用链表大的插入前面
        {
            enqueue(A[i]);
            i++
        }
        sum+= dequeue();
        cnt++;
        
    }    
    return -1;
}

#define QMAX 10000
int Q[QMAX]={0};
int wr=0;
int rd=0;
int QSize=0;
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



