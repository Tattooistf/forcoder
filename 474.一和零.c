/*
 * @lc app=leetcode.cn id=474 lang=c
 *
 * [474] 一和零
 *
 * https://leetcode-cn.com/problems/ones-and-zeroes/description/
 *
 * algorithms
 * Medium (53.38%)
 * Likes:    173
 * Dislikes: 0
 * Total Accepted:    10.7K
 * Total Submissions: 19.8K
 * Testcase Example:  '["10","0001","111001","1","0"]\n5\n3'
 *
 * 在计算机界中，我们总是追求用有限的资源获取最大的收益。
 * 
 * 现在，假设你分别支配着 m 个 0 和 n 个 1。另外，还有一个仅包含 0 和 1 字符串的数组。
 * 
 * 你的任务是使用给定的 m 个 0 和 n 个 1 ，找到能拼出存在于数组中的字符串的最大数量。每个 0 和 1 至多被使用一次。
 * 
 * 注意:
 * 
 * 
 * 给定 0 和 1 的数量都不会超过 100。
 * 给定字符串数组的长度不会超过 600。
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
 * 输出: 4
 * 
 * 解释: 总共 4 个字符串可以通过 5 个 0 和 3 个 1 拼出，即 "10","0001","1","0" 。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: Array = {"10", "0", "1"}, m = 1, n = 1
 * 输出: 2
 * 
 * 解释: 你可以拼出 "10"，但之后就没有剩余数字了。更好的选择是拼出 "0" 和 "1" 。
 * 
 * 
 */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
// @lc code=start
<<<<<<< Updated upstream


=======
>>>>>>> Stashed changes
int cmp(const void *a,const void *b)
{
    char *tmpa = *(char **)a;
    char *tmpb = *(char **)b;
    return strlen(tmpa)>strlen(tmpb);
}
<<<<<<< Updated upstream
#define max(a,b) ((a)>=(b)?(a):(b))

int findMaxForm(char ** strs, int strsSize, int m, int n){
    int res = 0;
    int cnt[601][2] = {0};
    int cnttotal[2] = {0};
    int dp[601][101][101] = {0};

    //qsort(strs,strsSize,sizeof(char *),cmp);
=======

int findMaxForm(char ** strs, int strsSize, int m, int n){
    int res = 0;
    int cnt[600][2] = {0};
    int cnttotal[2] = {0};

    qsort(strs,strsSize,sizeof(char *),cmp);
>>>>>>> Stashed changes
    for (int i = 0; i < strsSize; i++)
    {
        //printf("%s\n",strs[i]);
        for (int j = 0; j < strlen(strs[i]); j++)
        {
            if(strs[i][j] == '0')
            {
<<<<<<< Updated upstream
                cnt[i+1][0]++;
            }
            else
            {
                cnt[i+1][1]++;
            }
        }
    }

    for (int k = 1; k <= strsSize; k++) //cnt的起始为k为1，所以真实取值要-1
    {
        for (int i = 0; i <= m; i++) //从高到底和从低到高都可以，搞不懂？？？
        {
            for (int j = 0; j <= n; j++)
            {
                if (i >= cnt[k][0] && j >= cnt[k][1])
                {
                    dp[k][i][j] = max(dp[k-1][i][j],1+dp[k-1][i-cnt[k][0]][j-cnt[k][1]]);
                }
                else
                {
                    dp[k][i][j] = dp[k-1][i][j];
                }
            }
        }
    }
    
    return dp[strsSize][m][n];
}

// @lc code=end


// 推荐解法 但是没有搞明白什么时候从高到底，什么时候从低到高;应该是降维度导致的
#define max(a,b) ((a)>=(b)?(a):(b))
int findMaxForm(char ** strs, int strsSize, int m, int n){
    int dp[100+1][100+1] = {0};
    int cnt[600+1][2] = {0};

    //dp[0][0] = 0;
    //dp[0][1] = 0;

    for (int i = 0; i < strsSize; i++)
    {
        for (int j = 0; j < strlen(strs[i]); j++)
        {
            if(strs[i][j] == '0')
            {
=======
>>>>>>> Stashed changes
                cnt[i][0]++;
            }
            else
            {
                cnt[i][1]++;
            }
        }
    }
<<<<<<< Updated upstream

    for (int k = 0; k < strsSize; k++) 
    {
        for (int i = m; i >= 0; i--)  //不知掉从小到大不行，而从大到小可以？？？？
        {
            for (int j = n; j >= 0; j--)
            {
                if (i>=cnt[k][0] && j>=cnt[k][1])
                {
                    dp[i][j] = max(dp[i][j],dp[i-cnt[k][0]][j-cnt[k][1]]+1);
                }   
            }
        }
    }

    return dp[m][n];
}
=======
    
    for (int i = 0; i < strsSize; i++)
    {
        if ((cnttotal[0] + cnt[i][0]) <= m && (cnttotal[1] + cnt[i][1]) <= n)
        {
            res++;
            cnttotal[0]+=cnt[i][0];
            cnttotal[1]+=cnt[i][1];
        }
                
    }

    return res;
}
// @lc code=end
>>>>>>> Stashed changes


// 错误解题思路
int findMaxForm(char ** strs, int strsSize, int m, int n){
<<<<<<< Updated upstream
    int dp[100+1][100+1] = {0};
    int cnt[100+1][2] = {0};

    dp[0][0] = 0;
    dp[0][1] = 0;

    for (int i = 0; i < strsSize; i++)
    {
        for (int j = 0; j < strlen(strs[i]); j++)
        {
            if(strs[i][j] == '0')
            {
                cnt[i][0]++;
            }
            else
            {
                cnt[i][1]++;
            }
        }
    }

    for (int k = 0; k < strsSize; k++)
    {
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i>=cnt[k][0] && j>=cnt[k][1])
                {
                    dp[i][j] = max(dp[i][j],dp[i-cnt[k][0]][j-cnt[k][1]]+1);
                }   
            }
        }
    }
#if 0 //第一次解题80%，排序后累加，解题错误
    for (int i = 0; i < strsSize; i++)
    {
        if ((cnttotal[0] + cnt[i][0]) <= m && (cnttotal[1] + cnt[i][1]) <= n)
        {
            res++;
            cnttotal[0]+=cnt[i][0];
            cnttotal[1]+=cnt[i][1];
        }
                
    }

    return res;    
#endif
=======
    int dp[100][100] = {0};

    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[1][0] = 0;

    for (int i = 0; i < strsSize; i++)
    {
        if (strcmp(strs[i],"1"))
        {
            dp[0][1] = 1;
        }
        else if (strcmp(strs[i],"0"))
        {
            dp[1][0] = 1;
        }
    }
    
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = max(dp[i-1][j]+1,dp[i][j-1]+1);
        }
        
    }

>>>>>>> Stashed changes
    return dp[m][n];
}