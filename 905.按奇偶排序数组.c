/*
 * @lc app=leetcode.cn id=905 lang=c
 *
 * [905] 按奇偶排序数组
 *
 * https://leetcode-cn.com/problems/sort-array-by-parity/description/
 *
 * algorithms
 * Easy (69.93%)
 * Likes:    216
 * Dislikes: 0
 * Total Accepted:    56.2K
 * Total Submissions: 80.2K
 * Testcase Example:  '[3,1,2,4]'
 *
 * 给定一个非负整数数组 A，返回一个数组，在该数组中， A 的所有偶数元素之后跟着所有奇数元素。
 * 
 * 你可以返回满足此条件的任何数组作为答案。
 * 
 * 
 * 
 * 示例：
 * 
 * 输入：[3,1,2,4]
 * 输出：[2,4,3,1]
 * 输出 [4,2,3,1]，[2,4,1,3] 和 [4,2,1,3] 也会被接受。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= A.length <= 5000
 * 0 <= A[i] <= 5000
 * 
 * 
 */

// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* sortArrayByParity(int* nums, int numsSize, int* returnSize){
    int left = 0;
    int right = numsSize-1;
    int *ret = (int *)malloc(sizeof(int)*numsSize);

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i]%2 == 0)
        {
            ret[left++] = nums[i];
        }
        else
        {
            ret[right--] = nums[i];
        }
    }
    *returnSize = numsSize;
    return ret;
}
// @lc code=end


#define swap(a,b) {int tmp = (a);(a) = (b);(b) = tmp;}

int* sortArrayByParity(int* nums, int numsSize, int* returnSize){
    int right = numsSize-1;

    for (int i = 0; i < right; )
    {
        if (nums[i]%2 == 0)
        {
            //nums[left++] = nums[i];
            i++;
        }
        else
        {
            swap(nums[i],nums[right]);
            right--;
        }
    }
    *returnSize = numsSize;
    return nums;
}