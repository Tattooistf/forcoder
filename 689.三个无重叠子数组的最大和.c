/*
 * @lc app=leetcode.cn id=689 lang=c
 *
 * [689] 三个无重叠子数组的最大和
 *
 * https://leetcode-cn.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
 *
 * algorithms
 * Hard (47.08%)
 * Likes:    104
 * Dislikes: 0
 * Total Accepted:    2.4K
 * Total Submissions: 5.1K
 * Testcase Example:  '[1,2,1,2,6,7,5,1]\n2'
 *
 * 给定数组 nums 由正整数组成，找到三个互不重叠的子数组的最大和。
 * 
 * 每个子数组的长度为k，我们要使这3*k个项的和最大化。
 * 
 * 返回每个区间起始索引的列表（索引从 0 开始）。如果有多个结果，返回字典序最小的一个。
 * 
 * 示例:
 * 
 * 
 * 输入: [1,2,1,2,6,7,5,1], 2
 * 输出: [0, 3, 5]
 * 解释: 子数组 [1, 2], [2, 6], [7, 5] 对应的起始索引为 [0, 3, 5]。
 * 我们也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。
 * 
 * 
 * 注意:
 * 
 * 
 * nums.length的范围在[1, 20000]之间。
 * nums[i]的范围在[1, 65535]之间。
 * k的范围在[1, floor(nums.length / 3)]之间。
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSumOfThreeSubarrays(int* nums, int numsSize, int k, int* returnSize){
    int *preSum = (int *)malloc(sizeof(int)*numsSize);
    memset(preSum,0,sizeof(int)*numsSize);

    preSum[0] = nums[0];
    for (int i = 1; i < numsSize; i++)
    {
        preSum[i] = preSum[i-1] + nums[i];
        //printf("presum[%d]:%d\n",i,preSum[i]);大坑，逻辑错误，导致调试很长时间
    }

    for (int i = numsSize-1; i >= k; i--)
    {
        preSum[i] = preSum[i] - preSum[i-k];
    }
    

    int *left = (int *)malloc(sizeof(int)*numsSize);
    memset(left,0,sizeof(int)*numsSize);
    int max = k-1;
    for (int i = k-1; i < numsSize; i++)
    {
        if (preSum[i] > preSum[max])
        {
            max = i;
        }
        left[i] = max;
    }

    int *right = (int *)malloc(sizeof(int)*numsSize);
    memset(right,0,sizeof(int)*numsSize);
    max = numsSize-1;
    for (int i = numsSize-1; i >= (k-1); i--)
    {
        //printf("presum[%d]:%d\n",i,preSum[i]);
        if (preSum[i] >= preSum[max])
        {
            max = i;
        }
        right[i] = max;
    }    

    int *ret = (int*)malloc(sizeof(int)*3);
    ret[0] = ret[1] = ret[2] = -1;
    int maxsum = 0;
    for (int i = 2*k-1; i < (numsSize-k); i++)
    {
        int sum = preSum[i] + preSum[left[i-k]] + preSum[right[i+k]];
        if (ret[0] == -1 || sum > maxsum)
        {
            ret[0] = left[i-k]-k+1;
            ret[1] = i-k+1;
            ret[2] = right[i+k]-k+1;
            maxsum = sum;
        } 
    }
    
    *returnSize = 3;
    free(preSum);
    free(left);
    free(right);

    return ret;
}


// @lc code=end

int main()
{
    int *p = 0;
    int nums[] = {1,2,1,2,1,2,1,2,1};
    int size = 0;
    p = maxSumOfThreeSubarrays(nums,sizeof(nums)/sizeof(nums[0]),2,&size);
    return 0;
}