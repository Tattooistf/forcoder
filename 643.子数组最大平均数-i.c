/*
 * @lc app=leetcode.cn id=643 lang=c
 *
 * [643] 子数组最大平均数 I
 *
 * https://leetcode-cn.com/problems/maximum-average-subarray-i/description/
 *
 * algorithms
 * Easy (45.55%)
 * Likes:    186
 * Dislikes: 0
 * Total Accepted:    57.3K
 * Total Submissions: 126.1K
 * Testcase Example:  '[1,12,-5,-6,50,3]\n4'
 *
 * 给定 n 个整数，找出平均数最大且长度为 k 的连续子数组，并输出该最大平均数。
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 输入：[1,12,-5,-6,50,3], k = 4
 * 输出：12.75
 * 解释：最大平均数 (12-5-6+50)/4 = 51/4 = 12.75
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 k n 
 * 所给数据范围 [-10,000，10,000]。
 * 
 * 
 */

// @lc code=start
double findMaxAverage(int* nums, int numsSize, int k){
    int left = 0;
    int right = 0;
    double sum = 0.0;
    double max = INT_MIN;

    while (right < numsSize)
    {
        sum+=nums[right];
        if(right-left >= k-1)
        {
            max = max > sum ? max : sum;
            sum -= nums[left++];
        }
        right++;
    }
    return max/k;
}

// @lc code=end

double findMaxAverage(int* nums, int numsSize, int k){
    double sum = 0;
    for (int  i = 0; i < k; i++)
    {
        sum+=nums[i];
    }

    double max = sum;
    for (int i = k; i < numsSize; i++)
    {
        sum = sum + nums[i] - nums[i-k];
        max = max>sum?max:sum;
    }
    return max/k;
}
