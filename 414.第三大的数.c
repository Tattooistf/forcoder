/*
 * @lc app=leetcode.cn id=414 lang=c
 *
 * [414] 第三大的数
 *
 * https://leetcode-cn.com/problems/third-maximum-number/description/
 *
 * algorithms
 * Easy (35.75%)
 * Likes:    228
 * Dislikes: 0
 * Total Accepted:    53K
 * Total Submissions: 146.6K
 * Testcase Example:  '[3,2,1]'
 *
 * 给你一个非空数组，返回此数组中 第三大的数 。如果不存在，则返回数组中最大的数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：[3, 2, 1]
 * 输出：1
 * 解释：第三大的数是 1 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：[1, 2]
 * 输出：2
 * 解释：第三大的数不存在, 所以返回最大的数 2 。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：[2, 2, 3, 1]
 * 输出：1
 * 解释：注意，要求返回第三大的数，是指在所有不同数字中排第三大的数。
 * 此例中存在两个值为 2 的数，它们都排第二。在所有不同数字中排第三大的数为 1 。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * -2^31 
 * 
 * 
 * 
 * 
 * 进阶：你能设计一个时间复杂度 O(n) 的解决方案吗？
 * 
 */

// @lc code=start


int thirdMax(int* nums, int numsSize){
    int max = INT_MIN;  /* 最难的是数值正好等于32位的边界值 */
    int thd = INT_MIN;
    int sec = INT_MIN;
    int flag = 0;

    if (numsSize <=2)
    {
        if (numsSize == 2)
        {
            return nums[0]>nums[1]?nums[0]:nums[1];
        }
        return nums[0];
    }

    int tmp0;
    int tmp1;
    int tmp2;
    tmp0 = tmp1 = tmp2 = nums[0];
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != tmp0) /* 下面的代码来判断是否存在三个不同的数，技巧性很强 */
        {
            if (tmp0 != tmp1)
            {
                tmp2 = nums[i];
            }
            else
            {
                tmp1 = nums[i];
            }
        }
        
        if (nums[i]>max)
        {
            thd = sec;
            sec = max;
            max = nums[i];
            // flag++;
        }
        else if ((nums[i] > sec) &&(max != nums[i]))
        {
            thd = sec;
            sec = nums[i];
            // flag++;
        }
        else if ((nums[i] >= thd)&&(nums[i]!=max)&&(nums[i]!=sec))
        {
            thd = nums[i];
            // flag++;
        }
    }

    if (tmp0 == tmp2 || tmp1 == tmp2)
    {
        return max;
    }
    else
    {
        return thd;
    }
}
// @lc code=end


int thirdMax(int* nums, int numsSize){
    long max = LONG_MIN;  /* 最难的是数值正好等于32位的边界值 */
    long thd = LONG_MIN;
    long sec = LONG_MIN;
    int flag = 0;

    if (numsSize <=2)
    {
        if (numsSize == 2)
        {
            return nums[0]>nums[1]?nums[0]:nums[1];
        }
        return nums[0];
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i]>max)
        {
            thd = sec;
            sec = max;
            max = nums[i];
            // flag++;
        }
        else if ((nums[i] > sec) &&(max != nums[i]))
        {
            thd = sec;
            sec = nums[i];
            // flag++;
        }
        else if ((nums[i] >= thd)&&(nums[i]!=max)&&(nums[i]!=sec))
        {
            thd = nums[i];
            // flag++;
        }
    }
    return thd == LONG_MIN ? max : thd;
}