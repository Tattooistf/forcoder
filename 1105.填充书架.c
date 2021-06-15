/*
 * @lc app=leetcode.cn id=1105 lang=c
 *
 * [1105] 填充书架
 *
 * https://leetcode-cn.com/problems/filling-bookcase-shelves/description/
 *
 * algorithms
 * Medium (54.69%)
 * Likes:    103
 * Dislikes: 0
 * Total Accepted:    4.8K
 * Total Submissions: 8.6K
 * Testcase Example:  '[[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]]\n4'
 *
 * 附近的家居城促销，你买回了一直心仪的可调节书架，打算把自己的书都整理到新的书架上。
 * 
 * 你把要摆放的书 books 都整理好，叠成一摞：从上往下，第 i 本书的厚度为 books[i][0]，高度为 books[i][1]。
 * 
 * 按顺序 将这些书摆放到总宽度为 shelf_width 的书架上。
 * 
 * 先选几本书放在书架上（它们的厚度之和小于等于书架的宽度 shelf_width），然后再建一层书架。重复这个过程，直到把所有的书都放在书架上。
 * 
 * 需要注意的是，在上述过程的每个步骤中，摆放书的顺序与你整理好的顺序相同。 例如，如果这里有 5
 * 本书，那么可能的一种摆放情况是：第一和第二本书放在第一层书架上，第三本书放在第二层书架上，第四和第五本书放在最后一层书架上。
 * 
 * 每一层所摆放的书的最大高度就是这一层书架的层高，书架整体的高度为各层高之和。
 * 
 * 以这种方式布置书架，返回书架整体可能的最小高度。
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 
 * 输入：books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelf_width = 4
 * 输出：6
 * 解释：
 * 3 层书架的高度和为 1 + 3 + 2 = 6 。
 * 第 2 本书不必放在第一层书架上。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= books.length <= 1000
 * 1 <= books[i][0] <= shelf_width <= 1000
 * 1 <= books[i][1] <= 1000
 * 
 * 
 */

// @lc code=start
// 解题思路应该是DFS，或者DP动态规划
#define max(a,b) ((a)>(b)?(a): (b))
#define min(a,b) ((a)<(b)?(a): (b))
// 动态规划，dp[i]表示从i到最尾端的书架高度
void other(int ** books, int booksSize, int shelf_width, int start,int *dp)
{
    int width = 0;
    int height = 0;

    for (int i = start; i < booksSize; i++)
    {
        if (width + books[i][0] <= shelf_width)
        {
            width += books[i][0];
            height = max(height, books[i][1]);
            dp[start] = min(dp[start], height + dp[i+1]);
        }
        else
        {
            break;
        }
    }
    return;
}

int minHeightShelves(int** books, int booksSize, int* booksColSize, int shelf_width){
    int *dp = (int *)malloc(sizeof(int)*(booksSize+1));
    // memset(dp,0x7f,sizeof(int)*(booksSize+1));
    for (int i = 0; i < booksSize; i++)
    {
        dp[i] = INT_MAX;
    }
    dp[booksSize] = 0;

    for (int i = booksSize-1; i >= 0; i--)
    {
        other(books,booksSize,shelf_width,i,dp);
    }
    
    return dp[0];
}

// @lc code=end

// 解题思路应该是DFS，使用DFS会出现超时的问题，需要增加备忘录来优化性能
#define max(a,b) ((a)>(b)?(a): (b))
#define min(a,b) ((a)<(b)?(a): (b))

int dfs(int ** books, int booksSize, int shelf_width, int start, int *memo)
{
    int width = 0;
    int height = 0;
    int ans = INT_MAX;
    int ret = 0;
    if (start >= booksSize)
    {
        return 0;
    }

    if (memo[start] != 0)
    {
        return memo[start];
    }
    
    
    for (int i = start; i < booksSize; i++)
    {
        if (width + books[i][0] <= shelf_width)
        {
            width += books[i][0];
            height = max(height, books[i][1]);
            ret = height + dfs(books, booksSize,shelf_width,i+1,memo);
        }
        else
        {
            break;
        }
        ans = min(ret,ans);
    }
    memo[start] = ans; // 提前存储，后续直接获取，提升查询效率；不加这个会在7/20处超时

    return ans;
}

int minHeightShelves(int** books, int booksSize, int* booksColSize, int shelf_width){
    int* memo = (int *)malloc(sizeof(int)*booksSize);
    memset(memo,0,sizeof(int)*booksSize);
    int min = dfs(books,booksSize,shelf_width,0,memo);
    return min;
}


// 完全错误的思路，并且最后也没有解答出来
int comp(const void *a, const void *b)
{
    int *tmpa = *(int **)a;
    int *tmpb = *(int **)b;

    if (tmpa[1] < tmpb[1])
    {
        return 1;
    }
    else
    {
        if (tmpa[1] == tmpb[1])
        {
            return tmpa[0]>tmpb[0]?-1:1;
        }
        else
        {
            return -1;
        }
    }
}

int minHeightShelves(int** books, int booksSize, int* booksColSize, int shelf_width){
    int *presum = (int *)malloc(sizeof(int)*booksSize);
    int **bookbak = (int **)malloc(sizeof(int *)*booksSize);
    for (int i = 0; i < booksSize; i++)
    {
        bookbak[i] = (int *)malloc(sizeof(int)*3);
        bookbak[i][0] = books[i][0];
        bookbak[i][1] = books[i][1];
        bookbak[i][2] = i;

        presum[i] += bookbak[i][1];
    }
    qsort(bookbak,booksSize,sizeof(int *),comp);

    int len = 0;
    int high = 0;
    for (int i = 0; i < booksSize-1; i++)
    {
        int big = bookbak[i][2];
        int small = bookbak[i+1][2];
        if (presum[big] > shelf_width)
        {
            if (presum[big] - presum[small] > shelf_width)
            {
                high += bookbak[small-1][1];
            }
            else
            {
                int j = small;
                while (j>0 && presum[big]-presum[j] < shelf_width)
                {
                    j--;
                }
                
                high += books[j][1];
            }
            high += bookbak[i][1];
        }
    }
    return high;
}