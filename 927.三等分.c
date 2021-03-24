/*
 * @lc app=leetcode.cn id=927 lang=c
 *
 * [927] 三等分
 *
 * https://leetcode-cn.com/problems/three-equal-parts/description/
 *
 * algorithms
 * Hard (32.43%)
 * Likes:    46
 * Dislikes: 0
 * Total Accepted:    2.6K
 * Total Submissions: 8.1K
 * Testcase Example:  '[1,0,1,0,1]'
 *
 * 给定一个由 0 和 1 组成的数组 A，将数组分成 3 个非空的部分，使得所有这些部分表示相同的二进制值。
 * 
 * 如果可以做到，请返回任何 [i, j]，其中 i+1 < j，这样一来：
 * 
 * 
 * A[0], A[1], ..., A[i] 组成第一部分；
 * A[i+1], A[i+2], ..., A[j-1] 作为第二部分；
 * A[j], A[j+1], ..., A[A.length - 1] 是第三部分。
 * 这三个部分所表示的二进制值相等。
 * 
 * 
 * 如果无法做到，就返回 [-1, -1]。
 * 
 * 注意，在考虑每个部分所表示的二进制时，应当将其看作一个整体。例如，[1,1,0] 表示十进制中的 6，而不会是 3。此外，前导零也是被允许的，所以
 * [0,1,1] 和 [1,1] 表示相同的值。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：[1,0,1,0,1]
 * 输出：[0,3]
 * 
 * 
 * 示例 2：
 * 
 * 输出：[1,1,0,1,1]
 * 输出：[-1,-1]
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 3 <= A.length <= 30000
 * A[i] == 0 或 A[i] == 1
 * 
 * 
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start

int binSearch(int *arr,int start, int end, int val)
{
    int mid = 0;
    while (start < end)
    {
        mid = start + (end - start)/2;
        if (arr[mid] < val)
        {
            start = mid+1;
        }
        else
        {
            end = mid;
        }
    }
    
    return start;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* threeEqualParts(int* arr, int arrSize, int* returnSize){
    int *sum = (int *)malloc(sizeof(int)*arrSize);
    memset(sum,0,sizeof(int)*arrSize);
    int *ret = (int *)malloc(sizeof(int)*2);
    ret[0] = ret[1] = 0;
    *returnSize = 2;
    sum[0] = arr[0];
    for (int i = 1; i < arrSize; i++)
    {
        sum[i] = sum[i-1]+arr[i];
    }
    
    if (sum[arrSize-1]%3 != 0)
    {
        ret[0] = ret[1] = -1;
        free(sum);
        return ret;
    }
    if (sum[arrSize-1] == 0)
    {
        ret[0] = 0;
        ret[1] = arrSize-1;
        free(sum);
        return ret;
    }
    
    int pzs13 = binSearch(sum,0,arrSize,sum[arrSize-1]/3);
    int pzs23 = binSearch(sum,0,arrSize,sum[arrSize-1]*2/3);
    int zeroCount = 0;
    while (arr[arrSize-1-zeroCount] == 0)
    {
        zeroCount++;
    }
    
    int range1 = pzs13+zeroCount;
    int range2 = pzs23+zeroCount;
    int range3 = arrSize-1;
    while (range1>=0 && range1<pzs23 && (pzs13+zeroCount)<range2 && (pzs23+zeroCount)<range3)
    {
        if (arr[range1] == arr[range2] && arr[range2] == arr[range3])
        {
            range1--;
            range2--;
            range3--;
        }
        else
        {
            ret[0] = ret[1] = -1;
            free(sum);
            return ret;
        }
    }

    if (range3 == (arrSize-1))
    {
        ret[0] = ret[1] = -1;
    }
    else
    {
        ret[0] = pzs13+zeroCount;
        ret[1] = pzs23+zeroCount+1;
    }
    free(sum);
    
    return ret;
}
// @lc code=end

int main()
{
    int arr[] = {1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0};
    int num = 0;
    int *p = threeEqualParts(arr,sizeof(arr)/sizeof(arr[0]),&num);
    return 0;
}