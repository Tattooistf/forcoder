/*
 * @lc app=leetcode.cn id=213 lang=c
 *
 * [213] 打家劫舍 II
 *
 * https://leetcode-cn.com/problems/house-robber-ii/description/
 *
 * algorithms
 * Medium (37.03%)
 * Likes:    228
 * Dislikes: 0
 * Total Accepted:    27.4K
 * Total Submissions: 74K
 * Testcase Example:  '[2,3,2]'
 *
 * 
 * 你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 * 
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
 * 
 * 示例 1:
 * 
 * 输入: [2,3,2]
 * 输出: 3
 * 解释: 你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
 * 
 * 
 * 示例 2:
 * 
 * 输入: [1,2,3,1]
 * 输出: 4
 * 解释: 你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
 * 偷窃到的最高金额 = 1 + 3 = 4 。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start
#if 1
// 思路错误，最大值与次大值与最终解没有关系。还是第一次的思路正确，相邻三个的状态选择问题，应该使用动态规划

int rob(int* nums, int numsSize){
    int sum0=0;
    int sum1=0;

    if (nums==NULL || numsSize==0)
    {
        return 0;
    }

    int *array=(int *)malloc(numsSize*sizeof(nums[0]));
    int *temp=(int *)malloc(numsSize*sizeof(nums[0]));
    for (int i = 0; i < numsSize; i++)
    {
        array[i]=i;
        temp[i]=nums[i];
    }
    
    //  从大到小存储最大值的下标或位置
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i+1; j < numsSize; j++)
        {
            if (nums[array[i]]<nums[array[j]])
            {
                int tmp=array[i];
                array[i]=array[j];
                array[j]=tmp;
            }
        }
    }
//选最大值
    for (int i = 0; i < numsSize; i++)
    {
        if (temp[array[i]]==0)
        {
            continue;
        }
        sum0+=temp[array[i]];
        temp[(array[i]-1+numsSize)%numsSize]=0;
        temp[(array[i]+1)%numsSize]=0;
    }
// 选次大值
    memcpy(temp,nums,sizeof(int)*numsSize);
    for (int i = 1; i < numsSize; i++)
    {
        if (temp[array[i]]==0)
        {
            continue;
        }
        sum1+=temp[array[i]];
        temp[(array[i]-1+numsSize)%numsSize]=0;
        temp[(array[i]+1)%numsSize]=0;
    }    
    free(array);
    free(temp);
    return sum0>sum1?sum0:sum1;    
}
#else
int rob(int* nums, int numsSize){
    int sum0=0;
    int sum1=0;
    int index=0;

    if (nums==NULL || numsSize==0)
    {
        return 0;
    }

    if (numsSize==1)
    {
        return nums[0];
    }

    if (numsSize==2)
    {
        return nums[0]<nums[1]?nums[1]:nums[0];
    }

    if (numsSize==3)
    {
        return nums[0]>nums[2]?(nums[0]>nums[1]?nums[0]:nums[1]):(nums[2]>nums[1]?nums[2]:nums[1]);
    }
    int *temp=(int *)malloc(numsSize*sizeof(nums[0]));
    memset(temp,0,numsSize*sizeof(nums[0]));
    for (index = 0; index< numsSize; index++)
    {
        temp[index]=nums[index];
        if (index+2<numsSize)//temp存储选取该值后下一步能得到的值
        {
            temp[index]+=nums[index+2];
        }
    }
    
    index=0;// 从偶数开始遍历
    sum0+=nums[index];
    while (index+3<numsSize)
    {
        if (index+3<numsSize-1)//最后的数不能统计在内
        {
            sum0+= (temp[index+2]<temp[index+3])?nums[index+3]:nums[index+2];
            index=(temp[index+2]<temp[index+3])?(index+3):(index+2);
        }
        else
        {
            sum0+=nums[index+2];
            index=index+2;
        }
    }
    
    index=1;// 从奇数开始遍历
    sum1+=nums[index];
    while (index+2<numsSize)
    {
        if (index+3<numsSize)//可以统计最后一个数
        {
            sum1+= (temp[index+2]<temp[index+3])?nums[index+3]:nums[index+2];
            index=(temp[index+2]<temp[index+3])?(index+3):(index+2);
        }
        else
        {
            sum1+=nums[index+2];
            index=index+2;
        }
    }
    free(temp);
    return sum0>sum1?sum0:sum1;
}
#endif


// @lc code=end
int main(void)
{
    //[1,2,3,100,4,20,21,2000]
    int array[]={1,7,9,4};
    int ret=0;
    ret=rob(array,sizeof(array)/sizeof(array[0]));
    return 0;
}
