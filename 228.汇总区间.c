/*
 * @lc app=leetcode.cn id=228 lang=c
 *
 * [228] 汇总区间
 *
 * https://leetcode-cn.com/problems/summary-ranges/description/
 *
 * algorithms
 * Easy (58.52%)
 * Likes:    165
 * Dislikes: 0
 * Total Accepted:    50.7K
 * Total Submissions: 87K
 * Testcase Example:  '[0,1,2,4,5,7]'
 *
 * 给定一个无重复元素的有序整数数组 nums 。
 * 
 * 返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于
 * nums 的数字 x 。
 * 
 * 列表中的每个区间范围 [a,b] 应该按如下格式输出：
 * 
 * 
 * "a->b" ，如果 a != b
 * "a" ，如果 a == b
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [0,1,2,4,5,7]
 * 输出：["0->2","4->5","7"]
 * 解释：区间范围是：
 * [0,2] --> "0->2"
 * [4,5] --> "4->5"
 * [7,7] --> "7"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [0,2,3,4,6,8,9]
 * 输出：["0","2->4","6","8->9"]
 * 解释：区间范围是：
 * [0,0] --> "0"
 * [2,4] --> "2->4"
 * [6,6] --> "6"
 * [8,9] --> "8->9"
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = []
 * 输出：[]
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：nums = [-1]
 * 输出：["-1"]
 * 
 * 
 * 示例 5：
 * 
 * 
 * 输入：nums = [0]
 * 输出：["0"]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 
 * -2^31 
 * nums 中的所有值都 互不相同
 * nums 按升序排列
 * 
 * 
 */
#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char* tochar(int a, int b)
{
    char s[100] = {0};
    char *str = (char *)malloc(100*sizeof(char));
    if (a == b)
    {
        //itoa(a,str);
        sprintf(str, "%d", a);
    }
    else
    {
        //itoa(a, str);
        sprintf(str, "%d", a);
        //itoa(a, s);
        sprintf(s, "%d", b);        
        strcat(str,"->");
        strcat(str,s);
    }
    return str;
}

char ** summaryRanges(int* nums, int numsSize, int* returnSize){
    if (nums == NULL || numsSize == 0)
    {
        *returnSize = 0;
        return NULL;
    }

    int cnt = 0;
    int idx = 0;
    int start = 0;
    int end = 0;

    char **ret = (char **)malloc(sizeof(char *)*numsSize);
    memset(ret,0, sizeof(char *)*numsSize);
    if (numsSize == 1)
    {
        ret[idx++] = tochar(nums[start], nums[end]);
        *returnSize = idx;
        return ret;
    }
    
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] != (nums[i-1]+1) )
        {
            //end = (cnt>=1)?(i-1):start;
            end = i-1;
            ret[idx++] = tochar(nums[start], nums[end]);
            cnt = 0;
            start = i;
        }
        else
        {
            cnt++;
            continue;
        } 
    }
    ret[idx++] = tochar(nums[start], nums[numsSize-1]);
    *returnSize = idx;
    return ret;
}
// @lc code=end

