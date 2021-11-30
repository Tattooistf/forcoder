/*
 * @lc app=leetcode.cn id=327 lang=c
 *
 * [327] 区间和的个数
 *
 * https://leetcode-cn.com/problems/count-of-range-sum/description/
 *
 * algorithms
 * Hard (43.13%)
 * Likes:    349
 * Dislikes: 0
 * Total Accepted:    24.1K
 * Total Submissions: 56.8K
 * Testcase Example:  '[-2,5,-1]\n-2\n2'
 *
 * 给你一个整数数组 nums 以及两个整数 lower 和 upper 。求数组中，值位于范围 [lower, upper] （包含 lower 和
 * upper）之内的 区间和的个数 。
 * 
 * 区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [-2,5,-1], lower = -2, upper = 2
 * 输出：3
 * 解释：存在三个区间：[0,0]、[2,2] 和 [0,2] ，对应的区间和分别是：-2 、-1 、2 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [0], lower = 0, upper = 0
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * -2^31 
 * -10^5 
 * 题目数据保证答案是一个 32 位 的整数
 * 
 * 
 */

// @lc code=start

// 踩了个巨坑：参数应该是long *，错误的用成了int *；导致标准用例永远是两倍的结果
void merge(long *nums, int size, int left, int right, int l, int u, int *count)
{
    if (left==right)
    {
        *count = 0;
        return;
    }
    int mid = left+(right-left)/2;

    int n = 0;
    int m = 0;

    merge(nums,size,left,mid,l,u,&n);
    merge(nums,size,mid+1,right,l,u,&m);
    *count = m+n; // 先求两个数组内的，数组间的内容通过下面的语句解决；
    // printf("1:%d\n",*count);
    int j = mid+1;
    int k = mid+1;
    for (int i = left; i < mid+1; i++)
    {
        while (j <= right && nums[j]-nums[i] < l)
        {
            j++;
        }
        while (k <= right && nums[k]-nums[i] <= u)
        {
            k++;
        }
        *count += (k-j);
    }
    // printf("2:%d\n",*count);

    //  合并两个数组
    int lp = left;
    int rp = mid+1;
    int p = 0;
    long *arr = (long *)malloc(sizeof(long)*(right-left+1)); // 错误：数据应该是long类型，同时大小不是right
    while (lp <= mid || rp <= right)
    {
        if (lp>mid)
        {
            arr[p++] = nums[rp++];
        }
        else if (rp>right)
        {
            arr[p++] = nums[lp++];
        }
        else 
        {
            if (nums[lp] < nums[rp])
            {
                arr[p++] = nums[lp++];
            }
            else
            {
                arr[p++] = nums[rp++];
            }
        }
    }
    // memcpy(nums+left,arr,sizeof(long)*(right-left+1));
    // 错误：应该是从nums+left开始cpy，而不是nums
    for (int i = 0; i < right-left+1; i++)
    {
        nums[left+i] = arr[i];
    }
    free(arr);
    return;
}
// 暴力求解法超时，没有想到其他更好的方法；
// 后面看了题解，考虑使用归并排序，主要原因是排序后能快速计算，而前缀和之后的排序并不会对计算结果有影响
int countRangeSum(int* nums, int numsSize, int lower, int upper){
    int count = 0;
    long *sum = (long *)malloc(sizeof(long)*(numsSize+1));
    sum[0] = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum[i+1] = sum[i] + nums[i];
    }

    merge(sum,numsSize,0,numsSize,lower,upper,&count);
    free(sum);
    return count;
}
// @lc code=end

// 暴力求解法超时，没有想到其他更好的方法；
// 后面看了题解，考虑使用归并排序，主要原因是排序后能快速计算，而前缀和之后的排序并不会对计算结果有影响
int countRangeSum(int* nums, int numsSize, int lower, int upper){
    int count = 0;
    long *sum = (long *)malloc(sizeof(long)*(numsSize+1));
    sum[0] = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum[i+1] = sum[i] + nums[i];
    }

    for (int i = 0; i <= numsSize; i++)
    {
        for (int j = i+1; j <= numsSize; j++)
        {
            if((sum[j] - sum[i]) >= lower && (sum[j]-sum[i]) <= upper)
            {
                count++;
            }
        }
        
    }
    return count;
}