/*
 * @lc app=leetcode.cn id=1031 lang=c
 *
 * [1031] 两个非重叠子数组的最大和
 *
 * https://leetcode-cn.com/problems/maximum-sum-of-two-non-overlapping-subarrays/description/
 *
 * algorithms
 * Medium (55.60%)
 * Likes:    96
 * Dislikes: 0
 * Total Accepted:    4.4K
 * Total Submissions: 7.8K
 * Testcase Example:  '[0,6,5,2,2,5,1,9,4]\n1\n2'
 *
 * 给出非负整数数组 A ，返回两个非重叠（连续）子数组中元素的最大和，子数组的长度分别为 L 和 M。（这里需要澄清的是，长为 L 的子数组可以出现在长为
 * M 的子数组之前或之后。）
 * 
 * 从形式上看，返回最大的 V，而 V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ...
 * + A[j+M-1]) 并满足下列条件之一：
 * 
 * 
 * 
 * 
 * 0 <= i < i + L - 1 < j < j + M - 1 < A.length, 或
 * 0 <= j < j + M - 1 < i < i + L - 1 < A.length.
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
 * 输出：20
 * 解释：子数组的一种选择中，[9] 长度为 1，[6,5] 长度为 2。
 * 
 * 
 * 示例 2：
 * 
 * 输入：A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
 * 输出：29
 * 解释：子数组的一种选择中，[3,8,1] 长度为 3，[8,9] 长度为 2。
 * 
 * 
 * 示例 3：
 * 
 * 输入：A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
 * 输出：31
 * 解释：子数组的一种选择中，[5,6,0,9] 长度为 4，[0,3,8] 长度为 3。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * L >= 1
 * M >= 1
 * L + M <= A.length <= 1000
 * 0 <= A[i] <= 1000
 * 
 * 
 */

// @lc code=start

#define MAX(a, b) ((a) > (b) ? (a) : (b))
int maxSumTwoNoOverlap(int* nums, int numsSize, int firstLen, int secondLen){
    int *presum = (int *)malloc(sizeof(int)*(numsSize+1));
    memset(presum, 0, sizeof(int)*(numsSize+1));
    for (int i = 0; i < numsSize; i++)
    {
        presum[i+1] = presum[i] + nums[i];
        // nums[i] += nums[i-1] (i=1) 将第一个首数字漏掉了
    }

    int max = 0;
    for (int p = 0; (p+firstLen) <= numsSize; p++) // presum使用了i+1，所有边界应该多1个，<=才行
    {
        int sum = presum[p+firstLen] - presum[p];
        int sec = 0;
        for (int j = 0; (j+secondLen) <= numsSize; j++)
        {
            if ((j+secondLen <= p) || (j >= p+firstLen))
            {
                sec = MAX((presum[j+secondLen] - presum[j]),sec);
            }
        }
        max = MAX(max, sum+sec);
    }
    free(presum);
    return max;
}
// @lc code=end



#define MAX(a, b) ((a) > (b) ? (a) : (b))
int maxSumTwoNoOverlap(int* nums, int numsSize, int firstLen, int secondLen){
    int *presum = (int *)malloc(sizeof(int)*(numsSize+1));
    memset(presum, 0, sizeof(int)*(numsSize+1));
    for (int i = 0; i < numsSize; i++)
    {
        presum[i+1] = presum[i] + nums[i];
        // nums[i] += nums[i-1] (i=1) 将第一个首数字漏掉了
    }

    int max = 0;
    for (int p = 0; p <= (numsSize-firstLen); p++) // presum使用了i+1，所有边界应该多1个，<=才行
    {
        int sum = presum[p+firstLen] - presum[p];
        int sec = 0;
        int secmax = 0;
        for (int j = p+firstLen+1; j <= numsSize && (j+secondLen) <= numsSize; j++)
        {
            secmax = MAX((presum[j+secondLen] - presum[j]), secmax);
        }
        for (int j = 0; j <= p && (j+secondLen) <= p; j++)
        {
            sec = MAX((presum[j+secondLen] - presum[j]),sec);
        }  
        secmax = MAX(sec,secmax); 
        max = MAX(max, sum+secmax);
    }
    free(presum);
    return max;
}
