/*
 * @lc app=leetcode.cn id=1712 lang=c
 *
 * [1712] 将数组分成三个子数组的方案数
 *
 * https://leetcode-cn.com/problems/ways-to-split-array-into-three-subarrays/description/
 *
 * algorithms
 * Medium (28.44%)
 * Likes:    35
 * Dislikes: 0
 * Total Accepted:    3.1K
 * Total Submissions: 10.8K
 * Testcase Example:  '[1,1,1]'
 *
 * 我们称一个分割整数数组的方案是 好的 ，当它满足：
 * 
 * 
 * 数组被分成三个 非空 连续子数组，从左至右分别命名为 left ， mid ， right 。
 * left 中元素和小于等于 mid 中元素和，mid 中元素和小于等于 right 中元素和。
 * 
 * 
 * 给你一个 非负 整数数组 nums ，请你返回 好的 分割 nums 方案数目。由于答案可能会很大，请你将结果对 10^9 + 7 取余后返回。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,1,1]
 * 输出：1
 * 解释：唯一一种好的分割方案是将 nums 分成 [1] [1] [1] 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,2,2,5,0]
 * 输出：3
 * 解释：nums 总共有 3 种好的分割方案：
 * [1] [2] [2,2,5,0]
 * [1] [2,2] [2,5,0]
 * [1,2] [2,2] [5,0]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [3,2,1]
 * 输出：0
 * 解释：没有好的分割方案。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 3 
 * 0 
 * 
 * 
 */
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
// @lc code=start

// 前缀和做了修改从1开始，numsSize结束，才能全部通过；presum存储本人+前缀的方式有部分用例不过
int waysToSplit(int* nums, int numsSize){
    long long res = 0;
    if (numsSize < 3)
    {
        return 0;
    }

    int *preSum = (int *)malloc(sizeof(int)*(numsSize));
    memset(preSum,0,sizeof(int)*(numsSize));
    preSum[0] = nums[0];
    for (int i = 1; i < numsSize; i++)
    {
        preSum[i] = nums[i]+preSum[i-1];
    }
    int right = numsSize-1;
    int left = 0;
    int lSum = 0;
    int mSum = 0;
    int rSum = 0;
    for (int i = 0; i < numsSize; i++) // fix left
    {
        if (preSum[i]*3 > preSum[numsSize-1])
        {
            break;
        }
        left = i+1;
        right = numsSize-2;
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            mSum = preSum[mid] - preSum[i];//[i,mid]的和，应该包含nums[i]
            lSum = preSum[i];
            if (mSum == lSum)
            {
                right = mid - 1;
            }
            else if(mSum < lSum)
            {
                left = mid + 1;
            }
            else if (mSum > lSum)
            {
                right = mid - 1;
            }
        }
        int mleft = left;

        left = i+1;
        right = numsSize-2; //边界没有搞明白为什么需要使用-2才能行
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            rSum = preSum[numsSize-1] - preSum[mid];
            mSum = preSum[mid] - preSum[i];
            if (mSum == rSum)
            {
                left = mid + 1;
            }
            else if(mSum < rSum)
            {
                left = mid + 1;
            }
            else if (mSum > rSum)
            {
                right = mid - 1;
            }
        }
        int mright = right;
        if (mright >= mleft) //必须增加这个内容才能行,这个条件和上面的numsSize-2一起才能通过，否则在10w个0的时候会失败
        {
            res += mright - mleft + 1;
        }
        else
        {
            printf("%d-%d\n",mleft,mright);
        }
    }
    free(preSum);
    res = res % (int)(1e9+7);
    return res;
}
// @lc code=end
int array[] = {1,1,1};
int main(void)
{
    int i = waysToSplit(array,sizeof(array)/sizeof(array[0]));
    return 0;
}