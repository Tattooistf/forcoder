/*
 * @lc app=leetcode.cn id=665 lang=c
 *
 * [665] 非递减数列
 *
 * https://leetcode-cn.com/problems/non-decreasing-array/description/
 *
 * algorithms
 * Easy (26.57%)
 * Likes:    549
 * Dislikes: 0
 * Total Accepted:    62.8K
 * Total Submissions: 236.8K
 * Testcase Example:  '[4,2,3]'
 *
 * 给你一个长度为 n 的整数数组，请你判断在 最多 改变 1 个元素的情况下，该数组能否变成一个非递减数列。
 * 
 * 我们是这样定义一个非递减数列的： 对于数组中任意的 i (0 ，总满足 nums[i] 。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [4,2,3]
 * 输出: true
 * 解释: 你可以通过把第一个4变成1来使得它成为一个非递减数列。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [4,2,1]
 * 输出: false
 * 解释: 你不能在只改变一个元素的情况下将其变为非递减数列。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * - 10 ^ 5 
 * 
 * 
 */

// @lc code=start

int isValid(int *nums, int size)
{
    for (int i = 1; i < size; i++)
    {
        if (nums[i]>=nums[i-1])
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

bool checkPossibility(int* nums, int numsSize){
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i]<nums[i-1])
        {
            int a = nums[i];
            nums[i] = nums[i-1];
            if (isValid(nums,numsSize))
            {
                return true;
            }
            nums[i] = a;
            nums[i-1] = nums[i];
            if (isValid(nums,numsSize))
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
    }
    return true;
}

// @lc code=end


bool checkPossibility(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 1)
    {
        return true;
    }

    int count = 0;
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] >= nums[i-1])
        {
            continue;
        }
        else
        {
            if (i>=2 && nums[i]<nums[i-2])
            {
                nums[i] = nums[i-1];
            }
            else
            {
                nums[i-1] = nums[i];
            }
            count++;
        }
    }
    return count>1?false:true;
    
}