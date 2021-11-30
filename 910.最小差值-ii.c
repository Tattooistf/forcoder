/*
 * @lc app=leetcode.cn id=910 lang=c
 *
 * [910] 最小差值 II
 *
 * https://leetcode-cn.com/problems/smallest-range-ii/description/
 *
 * algorithms
 * Medium (31.03%)
 * Likes:    107
 * Dislikes: 0
 * Total Accepted:    6.4K
 * Total Submissions: 20.1K
 * Testcase Example:  '[1]\n0'
 *
 * 给你一个整数数组 A，对于每个整数 A[i]，可以选择 x = -K 或是 x = K （K 总是非负整数），并将 x 加到 A[i] 中。
 * 
 * 在此过程之后，得到数组 B。
 * 
 * 返回 B 的最大值和 B 的最小值之间可能存在的最小差值。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：A = [1], K = 0
 * 输出：0
 * 解释：B = [1]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：A = [0,10], K = 2
 * 输出：6
 * 解释：B = [2,8]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：A = [1,3,6], K = 3
 * 输出：3
 * 解释：B = [4,6,3]
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

// 并不是二分查找法，tag有问题
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
// 不看解答做不出来，关键还是+-k的边界，以及求最大最小值的方法，只比较两个头尾来确定最值，这个思想很赞，但很难想到
int smallestRangeII(int* nums, int numsSize, int k){
    qsort(nums,numsSize,sizeof(int),cmpmax);

    // 假定左半部+的操作到i位置，则i+1及以后都是-操作
    int ret = nums[numsSize-1]-nums[0];
    for (int i = 0; i < numsSize-1; i++)
    {
        int max = MAX(nums[numsSize-1]-k,nums[i]+k); // 错误：nums[numsSize-1]少减了k
        int min = MIN(nums[0]+k,nums[i+1]-k);
        ret = MIN(ret,(max-min));
    }
    return ret;
}
// @lc code=end

