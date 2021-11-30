/*
 * @lc app=leetcode.cn id=162 lang=c
 *
 * [162] 寻找峰值
 *
 * https://leetcode-cn.com/problems/find-peak-element/description/
 *
 * algorithms
 * Medium (48.57%)
 * Likes:    516
 * Dislikes: 0
 * Total Accepted:    125.2K
 * Total Submissions: 252.9K
 * Testcase Example:  '[1,2,3,1]'
 *
 * 峰值元素是指其值严格大于左右相邻值的元素。
 * 
 * 给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
 * 
 * 你可以假设 nums[-1] = nums[n] = -∞ 。
 * 
 * 你必须实现时间复杂度为 O(log n) 的算法来解决此问题。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,2,3,1]
 * 输出：2
 * 解释：3 是峰值元素，你的函数应该返回其索引 2。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,1,3,5,6,4]
 * 输出：1 或 5 
 * 解释：你的函数可以返回索引 1，其峰值元素为 2；
 * 或者返回索引 5， 其峰值元素为 6。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 1000
 * -2^31 <= nums[i] <= 2^31 - 1
 * 对于所有有效的 i 都有 nums[i] != nums[i + 1]
 * 
 * 
 */

// @lc code=start


int findPeakElement(int* nums, int numsSize){
    int left = 0;
    int right = numsSize-1; // 小技巧：前面right边界设定为numsize-1，所以mid+1一定不会越界

    if (numsSize == 1)
    {
        return 0;
    }
    int mid = 0;
    while (left < right)
    {
        mid = left + (right-left)/2;
        if (nums[mid] < nums[mid+1]) // 小技巧：前面right边界设定为numsize-1，所以mid+1一定不会越界
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}
// @lc code=end



int findPeakElement(int* nums, int numsSize){
    int left = 0;
    int right = numsSize;

    if (numsSize == 1)
    {
        return 0;
    }
    int mid = 0;
    while (left < right)
    {
        mid = left + (right-left)/2;
        if (nums[mid] < nums[mid-1])
        {
            right = mid;
            if (right <= 1) // 错误：当出现[2,1]情况时，必须判断，否则下标会异常
            {
                return 0;
            }
        }
        else
        {
            left = mid+1;
        }
    }
    return left == 0 ? 0 : left-1;
}
