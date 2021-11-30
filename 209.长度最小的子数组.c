/*
 * @lc app=leetcode.cn id=209 lang=c
 *
 * [209] 长度最小的子数组
 *
 * https://leetcode-cn.com/problems/minimum-size-subarray-sum/description/
 *
 * algorithms
 * Medium (45.19%)
 * Likes:    764
 * Dislikes: 0
 * Total Accepted:    188K
 * Total Submissions: 399.2K
 * Testcase Example:  '7\n[2,3,1,2,4,3]'
 *
 * 给定一个含有 n 个正整数的数组和一个正整数 target 。
 * 
 * 找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr]
 * ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：target = 7, nums = [2,3,1,2,4,3]
 * 输出：2
 * 解释：子数组 [4,3] 是该条件下的长度最小的子数组。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：target = 4, nums = [1,4,4]
 * 输出：1
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：target = 11, nums = [1,1,1,1,1,1,1,1]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 1 
 * 
 * 
 * 
 * 
 * 进阶：
 * 
 * 
 * 如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。
 * 
 * 
 */

// @lc code=start
// 
#define MIN(a,b) ((a)>(b)?(b):(a))

int binsearch(int *arr, int left, int right, int tar)
{
    int l = left;
    int r = right;
    while (l < r)
    {
        int mid = l+(r-l)/2;
        if (arr[mid] >= tar)
        {
            r = mid;
        }
        else
        {
            l = mid+1;
        }
    }
    return l;    
}

int minSubArrayLen(int target, int* nums, int numsSize){
    int *presum = (int *)malloc(sizeof(int)*(numsSize+1));
    presum[0] = 0;
    for (int i = 0; i < numsSize; i++)
    {
        presum[i+1] = nums[i]+presum[i];
    }

    int min = 0x0fffffff;
    for (int i = 1; i <= numsSize; i++)
    {
        if (presum[numsSize] < target+presum[i-1])
        {
            continue;
        }
        int psz = binsearch(presum,0,numsSize,target+presum[i-1]);
        min = MIN(min, psz-i+1);
    }
    free(presum);
    return (min == 0x0fffffff)?0:min;
}
// @lc code=end


// AC：最刚开始阅题错误，漏了两个条件：求>=target的值，求最小值，修正后AC
#define MIN(a,b) ((a)>(b)?(b):(a))
int minSubArrayLen(int target, int* nums, int numsSize){
    int left = 0;
    int right = 0;
    int sum = 0;
    int min = 0x0fffffff;

    while (right < numsSize)
    {
        sum += nums[right];
        while (sum >= target)
        {
            min = MIN(min, (right-left+1));
            sum -= nums[left];
            left++;
        }
        // if (sum == target)
        // {
        //     min = MIN(min, (right-left+1));
        // }
        right++;
    }
    return (min == 0x0fffffff) ? 0 : min;
}