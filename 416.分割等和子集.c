/*
 * @lc app=leetcode.cn id=416 lang=c
 *
 * [416] 分割等和子集
 *
 * https://leetcode-cn.com/problems/partition-equal-subset-sum/description/
 *
 * algorithms
 * Medium (49.48%)
 * Likes:    906
 * Dislikes: 0
 * Total Accepted:    158.9K
 * Total Submissions: 314K
 * Testcase Example:  '[1,5,11,5]'
 *
 * 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,5,11,5]
 * 输出：true
 * 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,3,5]
 * 输出：false
 * 解释：数组不能分割成两个元素和相等的子集。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 
 * 
 */

// @lc code=start
// 01背包问题，nums外循环，target内循环，倒序，target>=nums[i]
// 完全背包问题，nums外循环，target内循环，正序，target>=nums[i]
// 组合背包问题，target外循环，nums内循环，正序，target>=nums[i]

// 01背包的存在问题，其他类型还有最值问题、组合问题
bool canPartition(int* nums, int numsSize){
    int sum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum += nums[i];
    }

    if (sum%2)
    {
        return false;
    }
    
    int target = sum>>1;
    int *dp = (int *)malloc(sizeof(int)*(target+1));
    memset(dp,0,sizeof(int)*(target+1));
    dp[0] = 1;

    for (int i = 0; i < numsSize; i++)
    {
        for (int j = target; j >= nums[i]; j--)
        {
            dp[j] = dp[j] | dp[j-nums[i]]; // 错误：误将j用成了target，误将j用成i了
        }
    }
    
    return dp[target];
}
// @lc code=end

