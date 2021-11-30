/*
 * @lc app=leetcode.cn id=1139 lang=c
 *
 * [1139] 最大的以 1 为边界的正方形
 *
 * https://leetcode-cn.com/problems/largest-1-bordered-square/description/
 *
 * algorithms
 * Medium (46.64%)
 * Likes:    71
 * Dislikes: 0
 * Total Accepted:    8.7K
 * Total Submissions: 18.3K
 * Testcase Example:  '[[1,1,1],[1,0,1],[1,1,1]]'
 *
 * 给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大 正方形 子网格，并返回该子网格中的元素数量。如果不存在，则返回
 * 0。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
 * 输出：9
 * 
 * 
 * 示例 2：
 * 
 * 输入：grid = [[1,1,0,0]]
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= grid.length <= 100
 * 1 <= grid[0].length <= 100
 * grid[i][j] 为 0 或 1
 * 
 * 
 */

// @lc code=start

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 动态规划法,dp考虑错误，需要三维数组，表示左边连续1的个数和上边连续1的个数
int largest1BorderedSquare(int** grid, int gridSize, int* gridColSize){
    int ***dp = (int ***)malloc(sizeof(int**)*(gridSize+1));
    for (int i = 0; i <= gridSize; i++)
    {
        dp[i] = (int **)malloc(sizeof(int*)*(gridColSize[0]+1));// gridColSize[i] 会出现越界
        for (int j = 0; j <= gridColSize[0]; j++)
        {
            dp[i][j] = (int*)malloc(sizeof(int)*2);
            memset(dp[i][j], 0, sizeof(int)*2);
        }
    }
    
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridColSize[0]; j++)
        {
            if (grid[i][j] == 1) // 会出现越界
            {
                dp[i+1][j+1][0] = dp[i+1][j][0]+1;
                dp[i+1][j+1][1] = dp[i][j+1][1]+1;
            }
        }
    }
    
    int ret = 0;
    int maxret = 0;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridColSize[0]; j++)
        {
            int len = MIN(dp[i+1][j+1][0], dp[i+1][j+1][1]);
            for (int size = len; size > 0; size--)
            {
                if (dp[i-size+1+1][j+1][0] >= size && dp[i+1][j-size+1+1][1] >= size) // 最后的0，1方向搞错了
                {
                    ret = size;
                    break;
                }
            }
            maxret = MAX(ret, maxret);
        }
    }    
    // 需要释放内存
    return maxret*maxret;
}

// @lc code=end



// 暴力求解法
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int isInvalid(int **grid, int row, int col, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (grid[row+i][col] == 0 || grid[row][col+i] == 0 || grid[row+len-1][col+i] == 0 || grid[row+i][col+len-1] == 0)
        {
            return 1;
        }
    }
    return 0;
}

int largest1BorderedSquare(int** grid, int gridSize, int* gridColSize){
    int size = MIN(gridSize, gridColSize[0]);
    int ret = 0;

    for (int len = 1; len <= size; len++)
    {
        for (int j = 0; j < gridSize && j+len-1 < gridSize; j++)
        {
            for (int k = 0; k < gridColSize[0] && k+len-1 < gridColSize[0]; k++) // len相加的地方都少了个减1操作
            {
                if (isInvalid(grid, j,k,len) == 0)
                {
                    ret = MAX(len,ret);
                }
            }
        }
    }
    return ret*ret;
}
