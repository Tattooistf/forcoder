/*
 * @lc app=leetcode.cn id=912 lang=c
 *
 * [912] 排序数组
 *
 * https://leetcode-cn.com/problems/sort-an-array/description/
 *
 * algorithms
 * Medium (59.57%)
 * Likes:    351
 * Dislikes: 0
 * Total Accepted:    204.5K
 * Total Submissions: 360.8K
 * Testcase Example:  '[5,2,3,1]'
 *
 * 给你一个整数数组 nums，请你将该数组升序排列。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：nums = [5,2,3,1]
 * 输出：[1,2,3,5]
 * 
 * 
 * 示例 2：
 * 
 * 输入：nums = [5,1,1,2,0,0]
 * 输出：[0,0,1,1,2,5]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 50000
 * -50000 <= nums[i] <= 50000
 * 
 * 
 */

// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int cmpmax(const void *a, const void *b)
{
    int *tmpa = (int *)a;
    int *tmpb = (int *)b;
    if (*tmpa < *tmpb)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize){
    int *ret = (int *)malloc(sizeof(int)*numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        ret[i] = nums[i];
    }
    qsort(ret,numsSize,sizeof(int),cmpmax);
    *returnSize = numsSize;
    return ret;
}
// @lc code=end

