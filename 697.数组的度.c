/*
 * @lc app=leetcode.cn id=697 lang=c
 *
 * [697] 数组的度
 *
 * https://leetcode-cn.com/problems/degree-of-an-array/description/
 *
 * algorithms
 * Easy (60.75%)
 * Likes:    348
 * Dislikes: 0
 * Total Accepted:    62K
 * Total Submissions: 102.3K
 * Testcase Example:  '[1,2,2,3,1]'
 *
 * 给定一个非空且只包含非负数的整数数组 nums，数组的度的定义是指数组里任一元素出现频数的最大值。
 * 
 * 你的任务是在 nums 中找到与 nums 拥有相同大小的度的最短连续子数组，返回其长度。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：[1, 2, 2, 3, 1]
 * 输出：2
 * 解释：
 * 输入数组的度是2，因为元素1和2的出现频数最大，均为2.
 * 连续子数组里面拥有相同度的有如下所示:
 * [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
 * 最短连续子数组[2, 2]的长度为2，所以返回2.
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：[1,2,2,3,1,4,2]
 * 输出：6
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * nums.length 在1到 50,000 区间范围内。
 * nums[i] 是一个在 0 到 49,999 范围内的整数。
 * 
 * 
 */
#include "stdio.h"
#include "string.h"

// @lc code=start

// 改进版，直接在第一次求deg的时候将每个数的left和right计算出来，后面直接使用
int findShortestSubArray(int* nums, int numsSize){
    int deg[50000] = {0};
    int left[50000] = {0xFFFFFFFF}; // 当前mac的编译器上没法做到全部赋初值
    int right[50000] = {0xFFFFFFFF};
    int max = 0;
    int maxnum = 0;
    memset(deg,0,sizeof(deg)); 
    memset(left,0xff,sizeof(left));
    memset(right,0xff,sizeof(right));

    for (int i = 0; i < numsSize; i++)
    {
        if (left[nums[i]] == 0xFFFFFFFF)
        {
            left[nums[i]] = i;
        }
        right[nums[i]] = i;
        deg[nums[i]]++;
        max = max > deg[nums[i]]?max:deg[nums[i]];
        maxnum = maxnum>nums[i]?maxnum:nums[i];
    }

    int min = numsSize;
    for (int i = 0; i <= maxnum; i++)
    {
        if (max != deg[i])
        {
            continue;
        }
        min = min<(right[i]-left[i]+1)?min:(right[i]-left[i]+1);
    }
    return min;
}


// @lc code=end
int num[] = {2,1,1,2,1,3,3,3,1,3,1,3,2};

int main(void)
{
    int a = findShortestSubArray(num,sizeof(num)/sizeof(num[0]));
    return a;
}


int findShortestSubArray(int* nums, int numsSize){
    int deg[50000] = {0};
    int max = 0;
    int maxnum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        deg[nums[i]]++;
        max = max > deg[nums[i]]?max:deg[nums[i]];
    }

    int left = 0;
    int right = 0;
    int min = numsSize;
    memset(deg,0,sizeof(deg));
    while (right < numsSize) 
    {
        deg[nums[right]]++;
        while (max == deg[nums[right]]) // 标准的滑动窗口判断条件
        {
            min = min<(right-left+1)?min:(right-left+1);
            deg[nums[left]]--;
            left++;
        }
        right++;
    }
    return min; //因为是非空，所以不用考虑min == numsSize的场景
}

int findShortestSubArray(int* nums, int numsSize){
    int deg[50000] = {0};
    int max = 0;
    int maxnum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        deg[nums[i]]++;
        max = max > deg[nums[i]]?max:deg[nums[i]];
    }

    int left = 0;
    int right = 0;
    int min = numsSize;
    memset(deg,0,sizeof(deg));
    while (right < numsSize) // 知道用滑动窗口，但不太丝滑；内循环的条件使用错误了，效率影响不小。
    {
        deg[nums[right]]++;
        if (max > deg[nums[right]])
        {
            right++;
            continue;
        }
        // printf("right %d\n",right);
        while (max > deg[nums[left]])
        {
            deg[nums[left]]--;
            left++;
        }
        // printf("left %d\n",left);

        min = min<(right-left+1)?min:(right-left+1);
        right++;

        deg[nums[left]]--;
        left++;
    }
    return min;
}

int findShortestSubArray2(int* nums, int numsSize){
    int deg[50000] = {0};
    int max = 0;
    int maxnum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        deg[nums[i]]++;
        max = max > deg[nums[i]]?max:deg[nums[i]];
        maxnum = maxnum>nums[i]?maxnum:nums[i];
    }

    int min = numsSize;
    for (int i = 0; i <= maxnum; i++)
    {
        if (max != deg[i])
        {
            continue;
        }
        int sflag = 0;
        int start = 0;
        int end = 0;
        for (int j = 0; j < numsSize; j++)
        {
            if (nums[j] != i)
            {
                continue;
            }
            
            if (sflag == 0)
            {
                start = j;
                sflag = 1;
            }
            end = j;
        }
        min = min<(end-start+1)?min:(end-start+1);
    }
    return min;
}
