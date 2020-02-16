/*
 * @lc app=leetcode.cn id=994 lang=c
 *
 * [994] 腐烂的橘子
 *
 * https://leetcode-cn.com/problems/rotting-oranges/description/
 *
 * algorithms
 * Easy (46.15%)
 * Likes:    73
 * Dislikes: 0
 * Total Accepted:    7K
 * Total Submissions: 15K
 * Testcase Example:  '[[2,1,1],[1,1,0],[0,1,1]]'
 *
 * 在给定的网格中，每个单元格可以有以下三个值之一：
 * 
 * 
 * 值 0 代表空单元格；
 * 值 1 代表新鲜橘子；
 * 值 2 代表腐烂的橘子。
 * 
 * 
 * 每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。
 * 
 * 返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：[[2,1,1],[1,1,0],[0,1,1]]
 * 输出：4
 * 
 * 
 * 示例 2：
 * 
 * 输入：[[2,1,1],[0,1,1],[1,0,1]]
 * 输出：-1
 * 解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个正向上。
 * 
 * 
 * 示例 3：
 * 
 * 输入：[[0,2]]
 * 输出：0
 * 解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= grid.length <= 10
 * 1 <= grid[0].length <= 10
 * grid[i][j] 仅为 0、1 或 2
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include "math.h"
// @lc code=start
#define MAX 100
int wr=0,rd=0,qcnt=0;
int array[MAX]={-1};
void initq(void)
{
    wr=0;
    rd=0;
    qcnt=0;
    memset(array,-1,sizeof(int)*MAX);
    return;
}
int enqueue(int num)
{
    if (qcnt>=MAX)
    {
        return -1;
    }
    array[wr]=num;
    wr=(wr+1)%MAX;
    qcnt++;
    return 0;
}

int dequeue(void)
{
    if (qcnt==0)
    {
        return -1;
    }
    int tmp=rd;
    rd=(rd+1)%MAX;
    qcnt--;
    return array[tmp];
}

int qempty(void)
{
    return (qcnt==0)?1:0;
}

int getcount(void)
{
    return qcnt;
}
// 直接使用BFS解题，可能想复杂了，花了1个多小时
// 第一次qcnt忘记增减
// 第二次node求row时错误使用girdsize行数，应该使用列数*gridColSize
// 同时需要注意gridColSize应该是按照不同行获取不同的值，而不是下面直接取*gridColSize
int orangesRotting(int** grid, int gridSize, int* gridColSize){
    int count=0;// 新鲜的桔子数目
    int minu=0;
    initq();
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < *gridColSize; j++)
        {
            if (grid[i][j]==1)
            {
                count++;
            }
            if (grid[i][j]==2)
            {
                enqueue(i*(*gridColSize)+j);
            }
        }
    }
    if (count<=0)
    {
        return 0;
    }
    
    while (!qempty() && count>0)
    {
        int curcount = getcount();
        while (curcount>0)
        {
            int node=dequeue();
            int row=node/(*gridColSize);
            int col=node%(*gridColSize);
            if(row>0 && grid[row-1][col]==1) {grid[row-1][col]=2;enqueue((row-1)*(*gridColSize)+col);count--;}
            if(row<gridSize-1 && grid[row+1][col]==1) {grid[row+1][col]=2;enqueue((row+1)*(*gridColSize)+col);count--;}
            if(col>0 && grid[row][col-1]==1) {grid[row][col-1]=2;enqueue(row*(*gridColSize)+col-1);count--;}
            if(col<(*gridColSize-1) && grid[row][col+1]==1) {grid[row][col+1]=2;enqueue(row*(*gridColSize)+col+1);count--;}
            curcount--;
        }
        minu++;
    }

    if (count>0)
    {
        return -1;
    }
    return minu;    
}


// @lc code=end
int main(void)
{
    int A[2]={1,2};    
    int *array[1]={A};
    int col=2;
    int res=orangesRotting(array,1,&col);
    return 0;
}

