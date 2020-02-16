/*
 * @lc app=leetcode.cn id=289 lang=c
 *
 * [289] 生命游戏
 *
 * https://leetcode-cn.com/problems/game-of-life/description/
 *
 * algorithms
 * Medium (68.10%)
 * Likes:    104
 * Dislikes: 0
 * Total Accepted:    10.3K
 * Total Submissions: 15K
 * Testcase Example:  '[[0,1,0],[0,0,1],[1,1,1],[0,0,0]]'
 *
 * 根据百度百科，生命游戏，简称为生命，是英国数学家约翰·何顿·康威在1970年发明的细胞自动机。
 * 
 * 给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞具有一个初始状态 live（1）即为活细胞， 或
 * dead（0）即为死细胞。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：
 * 
 * 
 * 如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
 * 如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
 * 如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
 * 如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
 * 
 * 
 * 
 * 根据当前状态，写一个函数来计算面板上细胞的下一个（一次更新后的）状态。下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。
 * 
 * 示例:
 * 
 * 输入: 
 * [
 * [0,1,0],
 * [0,0,1],
 * [1,1,1],
 * [0,0,0]
 * ]
 * 输出: 
 * [
 * [0,0,0],
 * [1,0,1],
 * [0,1,1],
 * [0,1,0]
 * ]
 * 
 * 进阶:
 * 
 * 
 * 你可以使用原地算法解决本题吗？请注意，面板上所有格子需要同时被更新：你不能先更新某些格子，然后使用它们的更新后的值再更新其他格子。
 * 本题中，我们使用二维数组来表示面板。原则上，面板是无限的，但当活细胞侵占了面板边界时会造成问题。你将如何解决这些问题？
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


void gameOfLife(int** board, int boardSize, int* boardColSize){
    int **array=(int **)malloc(sizeof(int *)*(boardSize+2));
    memset(array,0,sizeof(int *)*(boardSize+2));
    for (int i = 0; i < boardSize+2; i++)
    {
        array[i]=(int *)malloc(sizeof(int)*(*boardColSize+2));
        memset(array[i],0,sizeof(int)*(*boardColSize+2));
    }
    
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < *boardColSize; j++)
        {
            array[i+1][j+1]=board[i][j];
        }   
    }
    
    for (int i = 1; i < boardSize+1; i++)
    {
        for (int j = 1; j < *boardColSize+1; j++)
        {
            int count=array[i-1][j-1]+array[i-1][j]+array[i-1][j+1];
            count+=array[i][j-1]+array[i][j+1];
            count+=array[i+1][j-1]+array[i+1][j]+array[i+1][j+1];
            if ((count<2 || count>3)&&array[i][j])
            {
                board[i-1][j-1]=0;
            }
            if ((count==2 || count==3)&&array[i][j])
            {
                board[i-1][j-1]=1;
            }
            if ((count==3)&&!array[i][j])
            {
                board[i-1][j-1]=1;
            }            
        } 
    }
    for (int i = 0; i < boardSize+2; i++)
    {
        free(array[i]);
        array[i]=NULL;
    }    
    free(array);
    array=NULL;
    
    return;
}


// @lc code=end
int board[3][3]={
    {1,0,1},
    {1,1,1},
    {0,1,0}
};

int main(void)
{
    int col=sizeof(board[0]);
    int row=sizeof(board)/sizeof(board[0]);
    gameOfLife(board,sizeof(board)/sizeof(board[0]),sizeof(board[0]));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ",board[i][j]);
        }
        printf("\n");
        
    }
    
    return 0;
}
