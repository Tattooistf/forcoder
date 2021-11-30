/*
 * @lc app=leetcode.cn id=410 lang=c
 *
 * [410] 分割数组的最大值
 *
 * https://leetcode-cn.com/problems/split-array-largest-sum/description/
 *
 * algorithms
 * Hard (54.28%)
 * Likes:    548
 * Dislikes: 0
 * Total Accepted:    38.6K
 * Total Submissions: 68.5K
 * Testcase Example:  '[7,2,5,10,8]\n2'
 *
 * 给定一个非负整数数组 nums 和一个整数 m ，你需要将这个数组分成 m 个非空的连续子数组。
 * 
 * 设计一个算法使得这 m 个子数组各自和的最大值最小。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [7,2,5,10,8], m = 2
 * 输出：18
 * 解释：
 * 一共有四种方法将 nums 分割为 2 个子数组。 其中最好的方式是将其分为 [7,2,5] 和 [10,8] 。
 * 因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,3,4,5], m = 2
 * 输出：9
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [1,4,4], m = 3
 * 输出：4
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * 1 
 * 
 * 
 */

// @lc code=start
#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)<(b)?(b):(a))

// 动态规划方法:比较难，三层循环的关系和边界很难把控
int splitArray(int* nums, int numsSize, int m){
    int *presum = (int *)malloc(sizeof(int)*(numsSize+1));
    presum[0] = 0;
    for (int i = 0; i < numsSize; i++)
    {
        presum[i+1] = presum[i] + nums[i];
    }
    int **dp = (int **)malloc(sizeof(int*)*(numsSize+1));
    for (int i = 0; i <= numsSize; i++)
    {
        dp[i] = (int *)malloc(sizeof(int)*(m+1));
        memset(dp[i],0x3f,sizeof(int)*(m+1));
        // dp[i][1] = presum[i+1];
    }
    dp[0][0] = 0;

    for (int i = 1; i <= numsSize; i++) // 错误：不知道为什么不能从0开始
    {
        for (int j = 1; j <= MIN(i,m); j++) // 直接为m也是可以的，效率低点
        {
            for (int k = 0; k < i; k++)
            {
                dp[i][j] = MIN(dp[i][j], MAX(dp[k][j-1],presum[i]-presum[k]));
            }
        }
    }
    return dp[numsSize][m];
}
// @lc code=end


// 思路：最刚开始想到了二分法，但是对left值如何确定没有想到好方法；
#define MAX(a,b) ((a)<(b)?(b):(a))
int func(int *arr, int size, int val)
{
    int sum = 0;
    int count = 1; // 错误：count应该从1开始
    for (int i = 0; i < size; i++)
    {
        if (sum + arr[i] > val)
        {
            count++;
            sum = arr[i];
        }
        else
        {
            sum += arr[i];
        }
    }
    
    return count;
}

int splitArray(int* nums, int numsSize, int m){
    int maxnum = 0;
    int sum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        maxnum = MAX(maxnum, nums[i]);
        sum += nums[i];
    }

    int left = maxnum;
    int right = sum;
    while (left <= right)
    {
        int mid = left + (right-left)/2;
        if (func(nums,numsSize,mid) > m) // 错误：实际上是count初始值的错误，但这个地方如果变成>=也能通过
        {
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }
    
    return left;
}


// 错误：思路应该算可以，但是解题出错25/30，在二分法判断条件上花费了很多时间
// 0,7,9,14,24,32
// 0,1,5,9
int binsearch(int *arr, int left, int right, int val)
{
    int l = left;
    int r = right;

    while (l < r)
    {
        int mid = l+(r-l)/2;
        if (abs(arr[mid]-val) > abs(arr[mid+1]-val))
        {
            l = mid+1;
        }
        else
        {
            r = mid;
        }
    }
    return l;
}
// 2,3,1,2,4,3
// 0,2,5,6,8,12,15
#define MAX(a,b) ((a)<(b)?(b):(a))
int findMin(int *presum, int start, int end, int m)
{
    // if (start >= end)
    // {
    //     return presum[end]-presum[start];
    // }
    
    if (m <= 1)
    {
        return presum[end]-presum[start];
    }
    int val = (presum[end]-presum[start])/m+presum[start];
    int tmp = binsearch(presum,start,end,val);
    int min = findMin(presum,tmp,end,m-1);
    int cur = presum[tmp]-presum[start];
    printf("m %d,val %d,start %d,cur %d,tmp %d,min %d\n",m,val,start,cur,tmp,min);
    return MAX(cur,min);
}

int splitArray(int* nums, int numsSize, int m){
    int *presum = (int *)malloc(sizeof(int)*(numsSize+1));
    presum[0] = 0;
    for (int i = 0; i < numsSize; i++)
    {
        presum[i+1] = nums[i] + presum[i];
    }
    int ret = findMin(presum,0,numsSize,m);
    free(presum);
    return ret;
}
