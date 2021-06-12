/* 
难度：Hard

给定一个包含 n 个整数的数组，找到最大平均值的连续子序列，且长度大于等于 k。并输出这个最大平均值。

样例 1:

输入: [1,12,-5,-6,50,3], k = 4
输出: 12.75
解释:
当长度为 5 的时候，最大平均值是 10.8，
当长度为 6 的时候，最大平均值是 9.16667。
所以返回值是 12.75。
1
2
3
4
5
6
注释 :

1 <= k <= n <= 10,000。
数组中的元素范围是 [-10,000, 10,000]。
答案的计算误差小于 10-5  */


// 解法一：暴力求解法，先计算K的最大平均值，再遍历K的范围
double findMaxAverage(int* nums, int numsSize, int k){
    int l = 0;
    double sum = 0.0;
    double avg = -10000;
    double max = -10000;
    for (int i = k; i <= numsSize; i++)
    {
        l = 0;
        sum = 0.0;
        max = -10000;
        for (int j = 0; j < numsSize; j++)
        {
            sum += nums[j];
            if (j-l >= i-1)
            {
                max = max > sum ? max : sum;
                sum -= nums[l++];
            }
            
        }
        avg = avg-(max/i) > 1e-5 ? avg : (max/i);
    }
    
    return avg;
}

// 解法二：快速寻找连续子数组的最值，可以使用前缀和；这道题有点类似前面做过的三分数组1712的情况，使用二分法和前缀和求解
// 想法非常的巧妙，特别是对前缀和的运用
int isValid(int *nums, int numsSize, int k, double avg)
{
    double sum = 0;
    double minPreSum = 0;
    double preSum = 0;

    int i = 0;
    for (i = 0; i < numsSize; i++)
    {
        sum += nums[i] - avg;
        if (i>=k)
        {
            preSum += nums[i-k] - avg;
            minPreSum = minPreSum > preSum ? preSum : minPreSum; // 寻找到间隔超过K的前缀最小值
            // maxSum  = maxSum > sum ? maxSum : sum; 个人理解，因为是从零开始累加过来的，所以不需要求最大值，总能覆盖到
        }

        if (sum - preSum > 0) // 为什么不是精度1e-5?
        {
            return true;
        }
    }    

    if (i>=numsSize)
    {
        return false;
    }
}

double findMaxAverage(int* nums, int numsSize, int k){
    double low = 10000;
    double high = -10000;

    for (int i = 0; i < numsSize; i++)
    {
        low = low < nums[i] ? low : nums[i];
        high = high > nums[i] ? high : nums[i];
    }
    
    while (high - low >= 1e-5) // 二分法快速遍历潜在的平均值
    {
        double mid = low + (high-low)/2;
        if (isValid(nums, numsSize, k, mid))
        {
            low = mid;    // double的精度，不能用+1来步进
        }
        else 
        {
            high = mid;
        }        
    }
    return low;    
}
