/*
 * @lc app=leetcode.cn id=518 lang=c
 *
 * [518] 零钱兑换 II
 *
 * https://leetcode-cn.com/problems/coin-change-2/description/
 *
 * algorithms
 * Medium (56.95%)
 * Likes:    584
 * Dislikes: 0
 * Total Accepted:    97.5K
 * Total Submissions: 150.1K
 * Testcase Example:  '5\n[1,2,5]'
 *
 * 给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
 * 
 * 请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。
 * 
 * 假设每一种面额的硬币有无限个。 
 * 
 * 题目数据保证结果符合 32 位带符号整数。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：amount = 5, coins = [1, 2, 5]
 * 输出：4
 * 解释：有四种方式可以凑成总金额：
 * 5=5
 * 5=2+2+1
 * 5=2+1+1+1
 * 5=1+1+1+1+1
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：amount = 3, coins = [2]
 * 输出：0
 * 解释：只用面额 2 的硬币不能凑成总金额 3 。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：amount = 10, coins = [10] 
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * coins 中的所有值 互不相同
 * 0 
 * 
 * 
 */

// @lc code=start

// 完全背包问题，组合类场景：nums外循环，target内循环，正序，target>=nums[i]
int change(int amount, int* coins, int coinsSize){
    int *dp = (int *)malloc(sizeof(int)*(amount+1));
    memset(dp,0,sizeof(int)*(amount+1));
    dp[0] = 1;
    for (int i = 0; i < coinsSize; i++)
    {
        for (int j = 0; j <= amount; j++)
        {
            if (j>=coins[i])
            {
                dp[j] += dp[j-coins[i]];
            }
        }
    }
    return dp[amount];
}
// @lc code=end

