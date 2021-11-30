/*
 * @lc app=leetcode.cn id=322 lang=c
 *
 * [322] 零钱兑换
 *
 * https://leetcode-cn.com/problems/coin-change/description/
 *
 * algorithms
 * Medium (42.72%)
 * Likes:    1434
 * Dislikes: 0
 * Total Accepted:    280.6K
 * Total Submissions: 634.8K
 * Testcase Example:  '[1,2,5]\n11'
 *
 * 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
 * 
 * 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
 * 
 * 你可以认为每种硬币的数量是无限的。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：coins = [1, 2, 5], amount = 11
 * 输出：3 
 * 解释：11 = 5 + 5 + 1
 * 
 * 示例 2：
 * 
 * 
 * 输入：coins = [2], amount = 3
 * 输出：-1
 * 
 * 示例 3：
 * 
 * 
 * 输入：coins = [1], amount = 0
 * 输出：0
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：coins = [1], amount = 1
 * 输出：1
 * 
 * 
 * 示例 5：
 * 
 * 
 * 输入：coins = [1], amount = 2
 * 输出：2
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 0 
 * 
 * 
 */

// @lc code=start

// 完全背包问题，外循环nums，内循环target，target>=nums[i]，正序遍历
#define MIN(a,b) ((a)>(b)?(b):(a))
int coinChange(int* coins, int coinsSize, int amount){
    int *dp = (int *)malloc(sizeof(int)*(amount+1));
    memset(dp,0x5a,sizeof(int)*(amount+1));
    dp[0] = 0; // 错误：初始的最小硬币个数应该是0，前面错误用成1
    for (int i = 0; i < coinsSize; i++)
    {
        for (int j = 0; j <= amount; j++)
        {
            if (j >= coins[i])
            {
                dp[j] = MIN(dp[j], dp[j-coins[i]]+1); // 差点错误：后者需要+1
            }
        }
        
    }
    return (dp[amount] == 0x5a5a5a5a)?-1:dp[amount];
}
// @lc code=end

