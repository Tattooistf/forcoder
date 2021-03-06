/*
 * @lc app=leetcode.cn id=51 lang=c
 *
 * [51] N皇后
 *
 * https://leetcode-cn.com/problems/n-queens/description/
 *
 * algorithms
 * Hard (70.74%)
 * Likes:    745
 * Dislikes: 0
 * Total Accepted:    102.2K
 * Total Submissions: 138.9K
 * Testcase Example:  '4'
 *
 * n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 * 
 * 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
 * 
 * 
 * 
 * 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 4
 * 输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * 解释：如上图所示，4 皇后问题存在两个不同的解法。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 1
 * 输出：[["Q"]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 皇后彼此不能相互攻击，也就是说：任何两个皇后都不能处于同一条横行、纵行或斜线上。
 * 
 * 
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
// @lc code=start
void backtrace(char **array, int level, int row, char ***ret, int *returnSize);
bool isValid(char **array, int level, int row, int col);
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** solveNQueens(int n, int* returnSize, int** returnColumnSizes){
    if (returnSize == NULL || returnColumnSizes == NULL)
    {
        return NULL;
    }

    char **array = (char **)malloc(sizeof(char)*n*(n+1));
    if (array == NULL)
    {
        return NULL;
    }
    memset(array,'.',sizeof(char)*n*(n+1));

    char ***ret = (char ***)malloc(sizeof(char**)*n*n*n);    
    backtrace(array, n, 0, ret, returnSize);
    *returnColumnSizes = (int *)malloc(sizeof(int)*(*returnSize));   
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = n;
    }
     
    free(array);
    return ret;
}

void backtrace(char **array, int level, int row, char ***ret, int *returnSize)
{
    if (row == level)
    {
        char **retarray = (char **)malloc(sizeof(char)*level*(level+1));
        memcpy(retarray,array,sizeof(char)*level*(level+1));
        ret[(*returnSize)++] = retarray;
        //记录返回值
        return;
    }

    for (int col = 0; col < level; col++)
    {
        if (!isValid(array, level, row, col))
        {
            continue;
        }        
        array[row][col] = 'Q';
        backtrace(array, level, row+1, ret, returnSize);
        array[row][col] = '.';
    }
    return;
}

bool isValid(char **array, int level, int row, int col)
{
    for (int i = 0; i < level; i++)
    {
        if (array[i][col] == 'Q')
        {
            return false;
        }
    }

    for (int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--)
    {
        if (array[i][j] == 'Q')
        {
            return false;
        }
    }

    for (int i = row-1, j = col+1; i >= 0 && j < level; i--,j++)
    {
        if (array[i][j] == 'Q')
        {
            return false;
        }
    }

    return true;
}
// @lc code=end

