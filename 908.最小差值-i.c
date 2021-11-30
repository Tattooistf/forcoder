/*
 * @lc app=leetcode.cn id=908 lang=c
 *
 * [908] 最小差值 I
 *
 * https://leetcode-cn.com/problems/smallest-range-i/description/
 *
 * algorithms
 * Easy (69.45%)
 * Likes:    72
 * Dislikes: 0
 * Total Accepted:    20.1K
 * Total Submissions: 28.8K
 * Testcase Example:  '[1]\n0'
 *
 * 给你一个整数数组 nums，请你给数组中的每个元素 nums[i] 都加上一个任意数字 x （-k ），从而得到一个新数组 result 。
 * 
 * 返回数组 result 的最大值和最小值之间可能存在的最小差值。
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1], k = 0
 * 输出：0
 * 解释：result = [1]
 * 
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [0,10], k = 2
 * 输出：6
 * 解释：result = [2,8]
 * 
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [1,3,6], k = 3
 * 输出：0
 * 解释：result = [3,3,3] or result = [4,4,4]
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * 0 
 * 
 * 
 */

// @lc code=start
// 当最大值最小值差值大于2k时候，max减少k，min+k就完事了，当小于2k的时候，由于差值绝对不可能为负数，因为差值为负数的时候，就违反了最大值最小值得悖论，结果无非最完美的情况下就是数组中所有的数值都一样
int cmpmax(const void *a, const void *b)
{
    int *tmpa = (int *)a;
    int *tmpb = (int *)b;

    if (*tmpa < *tmpb)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
// 没有想到，只需要max和min操作。做好理解的是max和min的差距与2k的关系
// 太过于数学推倒的方式，没有意义
int smallestRangeI(int* nums, int numsSize, int k){
    // qsort(nums,numsSize,sizeof(int),cmpmax); 不需要排序
    int max = nums[0];
    int min = nums[0];
    for (int i = 0; i < numsSize; i++)
    {
        max = MAX(max, nums[i]);
        min = MIN(min, nums[i]);
    }
    return MAX(0, max-k-(min+k));
}
// @lc code=end

