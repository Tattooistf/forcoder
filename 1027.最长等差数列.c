/*
 * @lc app=leetcode.cn id=1027 lang=c
 *
 * [1027] 最长等差数列
 *
 * https://leetcode-cn.com/problems/longest-arithmetic-subsequence/description/
 *
 * algorithms
 * Medium (44.02%)
 * Likes:    131
 * Dislikes: 0
 * Total Accepted:    11.4K
 * Total Submissions: 26.4K
 * Testcase Example:  '[3,6,9,12]'
 *
 * 给定一个整数数组 A，返回 A 中最长等差子序列的长度。
 * 
 * 回想一下，A 的子序列是列表 A[i_1], A[i_2], ..., A[i_k] 其中 0 <= i_1 < i_2 < ... < i_k <=
 * A.length - 1。并且如果 B[i+1] - B[i]( 0 <= i < B.length - 1) 的值都相同，那么序列 B
 * 是等差的。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：[3,6,9,12]
 * 输出：4
 * 解释： 
 * 整个数组是公差为 3 的等差数列。
 * 
 * 
 * 示例 2：
 * 
 * 输入：[9,4,7,2,10]
 * 输出：3
 * 解释：
 * 最长的等差子序列是 [4,7,10]。
 * 
 * 
 * 示例 3：
 * 
 * 输入：[20,1,15,3,10,5,8]
 * 输出：4
 * 解释：
 * 最长的等差子序列是 [20,15,10,5]。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= A.length <= 2000
 * 0 <= A[i] <= 10000
 * 
 * 
 */

// @lc code=start
// 思路错误，第一次想的是使用差分数组，固定两个数再遍历第三个，发现成为了暴力法，且思路没理清楚，解题失败

// 动态规划：参考LIS实现原理,原理基本一致
#define MAX(a,b) ((a)>(b)?(a):(b))
int longestArithSeqLength(int* nums, int numsSize){
    int count = 0;
    int max = 0;
    int **dp = malloc(sizeof(int *)*numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        dp[i] = (int *)malloc(sizeof(int)*20000);
        memset(dp[i], 0, sizeof(int)*20000); // 此处修改性能提升70%
        // for (int j = 0; j < 20000; j++)
        // {
        //     dp[i][j] = 1;
        // }
    }
    
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int delta = nums[i] - nums[j];
            delta += 10000; // 避免dp下标为负
            dp[i][delta] = MAX(dp[i][delta], dp[j][delta]+1);
            max = MAX(max, dp[i][delta]);
        }
    }

    for (int i = 0; i < numsSize; i++)
    {
        free(dp[i]);
    }
    free(dp);
    
    return max+1;
}

// @lc code=end
int arr[] = {12,28,13,6,34,36,53,24,29,2,23,0,22,25,53,34,23,50,35,43,53,11,48,56,44,53,31,6,31,57,46,6,17,42,48,28,5,24,0,14,43,12,21,6,30,37,16,56,19,45,51,10,22,38,39,23,8,29,60,18};
int main(void)
{
    int output = longestArithSeqLength(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}



// 暴力法，出现超时；但两句简单的语句却出现不少问题，值得深思
int longestArithSeqLength(int* nums, int numsSize){
    int count = 0;
    int max = 0;
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i+1; j < numsSize; j++)
        {
            count = 2;
            int tmpj = j;
            int tmpi = i;
            for (int k = j+1; k < numsSize; k++)
            {
                if ((nums[k] + nums[tmpi]) == 2*nums[tmpj])
                {
                    count++;
                    // printf("%d-%d-%d  ",tmpi,tmpj,k);
                    tmpi = tmpj; // 教训啊，tmpj写成了j，导致下面的用例失败
                    tmpj = k;
                    // 第二个教训，两句话的顺序搞反，导致奇怪的问题
                    // 看似不关键的两句话，却出现好几个问题
                }
            }
            // printf("\n");
            max = max < count ? count : max;
            // printf("max %d, count %d\n",max,count);
        }
    }
    return max;
}