/*
 * @lc app=leetcode.cn id=494 lang=c
 *
 * [494] 目标和
 *
 * https://leetcode-cn.com/problems/target-sum/description/
 *
 * algorithms
 * Medium (44.88%)
 * Likes:    874
 * Dislikes: 0
 * Total Accepted:    138.4K
 * Total Submissions: 276.1K
 * Testcase Example:  '[1,1,1,1,1]\n3'
 *
 * 给你一个整数数组 nums 和一个整数 target 。
 * 
 * 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
 * 
 * 
 * 例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
 * 
 * 
 * 返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,1,1,1,1], target = 3
 * 输出：5
 * 解释：一共有 5 种方法让最终目标和为 3 。
 * -1 + 1 + 1 + 1 + 1 = 3
 * +1 - 1 + 1 + 1 + 1 = 3
 * +1 + 1 - 1 + 1 + 1 = 3
 * +1 + 1 + 1 - 1 + 1 = 3
 * +1 + 1 + 1 + 1 - 1 = 3
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1], target = 1
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * 0 
 * -1000 
 * 
 * 
 */

// @lc code=start

// 错误：需要想到neg、sum-neg、target的关系，sum-neg-neg = target
// 将问题转变为选择数字使其和为neg,01背包的组合问题
int findTargetSumWays(int* nums, int numsSize, int target){
    int sum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum += nums[i];
    }
    int diff = sum-target;
    if (diff%2 || diff < 0) // 错误：忘记判断负数的情况
    {
        return 0;
    }
    diff = diff>>1;
    int *dp = (int *)malloc(sizeof(int)*(diff+1)); // 错误：diff错误用成了target
    memset(dp, 0, sizeof(int)*(diff+1));
    dp[0] = 1;

    for (int i = 0; i < numsSize; i++)
    {
        for (int j = diff; j >= nums[i]; j--)
        {
            dp[j] += dp[j-nums[i]];
        }
    }
    return dp[diff];
}
// @lc code=end

