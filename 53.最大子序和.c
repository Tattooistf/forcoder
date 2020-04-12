/*
 * @lc app=leetcode.cn id=53 lang=c
 *
 * [53] 最大子序和
 *
 * https://leetcode-cn.com/problems/maximum-subarray/description/
 *
 * algorithms
 * Easy (49.98%)
 * Likes:    1817
 * Dislikes: 0
 * Total Accepted:    201K
 * Total Submissions: 401.2K
 * Testcase Example:  '[-2,1,-3,4,-1,2,1,-5,4]'
 *
 * 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 * 
 * 示例:
 * 
 * 输入: [-2,1,-3,4,-1,2,1,-5,4],
 * 输出: 6
 * 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
 * 
 * 
 * 进阶:
 * 
 * 如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。
 * 
 */

// @lc code=start

#define max(a,b) ((a)>(b)?(a):(b))

int maxSubArray(int* nums, int numsSize){
    int *dp=(int*)malloc(sizeof(int)*(numsSize+1));
    memset(dp,0,sizeof(int)*numsSize);
    int res=nums[0];

    for (int i = 0; i < numsSize; i++)
    {
        dp[i+1]=max(dp[i]+nums[i],nums[i]);
        res=max(dp[i+1],res);
    }
    return res;
}


// @lc code=end

