/*
 * @lc app=leetcode.cn id=137 lang=c
 *
 * [137] 只出现一次的数字 II
 *
 * https://leetcode-cn.com/problems/single-number-ii/description/
 *
 * algorithms
 * Medium (66.57%)
 * Likes:    311
 * Dislikes: 0
 * Total Accepted:    27.8K
 * Total Submissions: 41.7K
 * Testcase Example:  '[2,2,3,2]'
 *
 * 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。
 * 
 * 说明：
 * 
 * 你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
 * 
 * 示例 1:
 * 
 * 输入: [2,2,3,2]
 * 输出: 3
 * 
 * 
 * 示例 2:
 * 
 * 输入: [0,1,0,1,0,1,99]
 * 输出: 99
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// 这题没有任何思路，就想到了是位操作的题目；后来看过解答提示后才知道思路
// 1、对每一位求出现次数后模上3，就表示该位出现1的次数

// @lc code=start


int singleNumber(int* nums, int numsSize){
    int A[32] = {0};

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < numsSize; j++)
        {
            /* if ((nums[j]>>i) & 0x1)
            {
                A[i]++;
            }*/
            // 优化
            A[i] += (nums[j] >> i) & 0x1;
        }
        A[i] %= 3;
    }
    unsigned int res = 0;
    for (int i = 31; i >= 0; i--)
    {
        res |= (unsigned int)A[i] << i;
    }
    return (int)res;    
}


// @lc code=end

