/*
 * @lc app=leetcode.cn id=377 lang=c
 *
 * [377] 组合总和 Ⅳ
 *
 * https://leetcode-cn.com/problems/combination-sum-iv/description/
 *
 * algorithms
 * Medium (42.18%)
 * Likes:    156
 * Dislikes: 0
 * Total Accepted:    12.6K
 * Total Submissions: 29.7K
 * Testcase Example:  '[1,2,3]\n4'
 *
 * 给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
 * 
 * 示例:
 * 
 * 
 * nums = [1, 2, 3]
 * target = 4
 * 
 * 所有可能的组合为：
 * (1, 1, 1, 1)
 * (1, 1, 2)
 * (1, 2, 1)
 * (1, 3)
 * (2, 1, 1)
 * (2, 2)
 * (3, 1)
 * 
 * 请注意，顺序不同的序列被视作不同的组合。
 * 
 * 因此输出为 7。
 * 
 * 
 * 进阶：
 * 如果给定的数组中含有负数会怎么样？
 * 问题会产生什么变化？
 * 我们需要在题目中添加什么限制来允许负数的出现？
 * 
 * 致谢：
 * 特别感谢 @pbrother 添加此问题并创建所有测试用例。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
// @lc code=start
int combinationSum4(int* nums, int numsSize, int target){
    unsigned int *dp = (unsigned int *)malloc(sizeof(unsigned int)*(target+1));
    memset(dp,0,sizeof(unsigned int)*(target+1));
    dp[0] = 1;
    for (int i = 1; i <= target; i++) //int 会出现越界的情况，需要考虑使用long long
    {
        for (int j = 0; j < numsSize; j++)
        {
            if (i >= nums[j])
            {
                dp[i] = dp[i] + dp[i-nums[j]];
            }
        }
    }
    
    return dp[target];
}

// @lc code=end

int main(void)
{
    int nums[] = {1,2,3};
    int target = 4;
    int res = combinationSum4(nums,sizeof(nums)/sizeof(nums[0]),target);
    printf("res = %d \n",res);
    return 0;
}


// 直观第一次解题直接使用组合的常见方法dfs，出现解题超时，且想不到更好的方式
void dfs(int* nums,int numsSize, int target,int sum,int *count)
{
    #if 0
    if (sum >= target)
    {
        return;
    }
    #endif

    for (int i = 0; i < numsSize; i++)
    {
        if (sum+nums[i] == target)
        {
            (*count)++;
            return;
        }

        if (sum+nums[i] > target)
        {
            return;
        }
        dfs(nums,numsSize,target,sum+nums[i],count);
    }
    return;
}

int cmp(const void *a,const void *b)
{
    int *numa = (int *)a;
    int *numb = (int *)b;
    return *numa > *numb;
}

int combinationSum41(int* nums, int numsSize, int target){
    int count = 0;
    qsort(nums,numsSize,sizeof(nums[0]),cmp);
    dfs(nums,numsSize,target,0,&count);
    return count;
}
