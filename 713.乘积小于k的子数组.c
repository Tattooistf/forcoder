/*
 * @lc app=leetcode.cn id=713 lang=c
 *
 * [713] 乘积小于K的子数组
 *
 * https://leetcode-cn.com/problems/subarray-product-less-than-k/description/
 *
 * algorithms
 * Medium (37.67%)
 * Likes:    252
 * Dislikes: 0
 * Total Accepted:    14.9K
 * Total Submissions: 39K
 * Testcase Example:  '[10,5,2,6]\n100'
 *
 * 给定一个正整数数组 nums。
 * 
 * 找出该数组内乘积小于 k 的连续的子数组的个数。
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [10,5,2,6], k = 100
 * 输出: 8
 * 解释: 8个乘积小于100的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
 * 需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
 * 
 * 
 * 说明:
 * 
 * 
 * 0 < nums.length <= 50000
 * 0 < nums[i] < 1000
 * 0 <= k < 10^6
 * 
 * 
 */

// @lc code=start
// 一上来就想到了滑动窗口，但是对于增加count的运算逻辑没有搞清楚，为什么是增加r-l+1个数组
// 比较难的就是想到滑动窗口每次增加的值是right-left+1
int numSubarrayProductLessThanK(int* nums, int numsSize, int k){
    int left = 0;
    int right = 0;
    int mul = 1;
    int count = 0;

    if (k<=1)
    {
        return 0;
    }

    while (right < numsSize)
    {
        mul *= nums[right];
        while (mul >= k)
        {
            mul /= nums[left];
            left++;
        }
        count+=right-left+1;
        right++;
    }

    return count;
}
// @lc code=end


int numSubarrayProductLessThanK(int* nums, int numsSize, int k){
    int left = 0;
    int right = 0;
    int mul = 1;
    int count = 0;

    while (left < numsSize && right < numsSize)
    {
        mul *= nums[right];
        right++;
        if (mul >= k)
        {
            // mul /= nums[left];
            left++;
            // count+=;
            right = left;
            mul = 1;
            continue;
        }
        count++;

        /* code */
    }
    if (right > left+1)
    {
        count += right -left;
    }
    
    return count;
}



// 暴力求解直接超时，84个用例通过75个
int numSubarrayProductLessThanK(int* nums, int numsSize, int k){
    int left = 0;
    int right = 0;
    int mul = 1;
    int count = 0;

    for (int i = 0; i < numsSize; i++)
    {
        mul = 1;
        for (int j = i; j < numsSize; j++)
        {
            mul *= nums[j];
            if (mul >= k)
            {
                break;
            }
            count++;
        }   
    }
    
    return count;
}