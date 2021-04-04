/*
 * @lc app=leetcode.cn id=485 lang=c
 *
 * [485] 最大连续 1 的个数
 *
 * https://leetcode-cn.com/problems/max-consecutive-ones/description/
 *
 * algorithms
 * Easy (60.09%)
 * Likes:    224
 * Dislikes: 0
 * Total Accepted:    100.4K
 * Total Submissions: 167.5K
 * Testcase Example:  '[1,0,1,1,0,1]'
 *
 * 给定一个二进制数组， 计算其中最大连续 1 的个数。
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 输入：[1,1,0,1,1,1]
 * 输出：3
 * 解释：开头的两位和最后的三位都是连续 1 ，所以最大连续 1 的个数是 3.
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 输入的数组只包含 0 和 1 。
 * 输入数组的长度是正整数，且不超过 10,000。
 * 
 * 
 */

// @lc code=start

int Max(int a,int b)
{
    return  a>b?a:b;
}

int findMaxConsecutiveOnes(int* nums, int numsSize){
    int count = 0;
    int max = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] == 1)
        {
            count++;
        }
        else
        {
            max = Max(max,count);
            count = 0;
        }
    }
    max = Max(max,count);
    return max;
}


// @lc code=end

