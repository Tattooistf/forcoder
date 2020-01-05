#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

//题目过于复杂，还没有将逻辑搞清楚，当前先考虑使用动态规划实现，但是与正式的解题思路有偏差，明天再看解答尝试下。
/*
 * 华华假期的时候独自去南京玩，出发前他想制定一个旅行计划。假设南京有N个景点，华华给每个景点定义了一个开心值Si，也就是说当他游玩这个景点后
 * 他的总开心值会加Si，同时游玩第i个景点会花费Ci的时间。由于没有妹子陪伴，所以他想在限定的时间T内，从起点S，有选择的游玩一些景点，最终到达终点E。当然
 * 他想让这次旅行所得的开心值最大。
 * 注意，华华可以为了走近路而只是路过一些景点，不去游玩，包括E和S。而且他有一个怪癖就是要去玩的下一个景点的开心值一定要大于之前玩的景点（例如，他游玩
 * 景点i获得的开心值为10，那么他游玩的下一个景点的开心值必须大于10）。此外，景点间的路是双向的，路上也要耗费时间，而且各个点之间可能不会一条路，华华当
 * 然会走最短的路
 * 
 */

int main(void)
{
    return 0;
}

/*
 * 典型的背包问题，可以考虑动态规划算法
 * 迁移方程式 V(n)=V(n-1)+Si T(n)=T(n-1)+Ci
 * Si n > Si n-1
 * Ci是最短的路程
 * 迁移条件
 */
#define N 100 //景点数
#define T 10 //天数
int dp[N][T]={0};
int V[N]={0};
int Si[N]={0};
int Ci[N]={0};

void cal()
{
    for (int i = 0; i < T; i++)
    {
        dp[0][i]=i;
    }
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < T; j++)
        {
            dp[i][j]=max(dp[i-1][j]),Si+dp[i-1][j-Ci];
        }
        
    }
    return dp[N][T];
}


