/*
 * @lc app=leetcode.cn id=978 lang=c
 *
 * [978] 最长湍流子数组
 *
 * https://leetcode-cn.com/problems/longest-turbulent-subarray/description/
 *
 * algorithms
 * Medium (47.23%)
 * Likes:    158
 * Dislikes: 0
 * Total Accepted:    37.8K
 * Total Submissions: 80K
 * Testcase Example:  '[9,4,2,10,7,8,8,1,9]'
 *
 * 当 A 的子数组 A[i], A[i+1], ..., A[j] 满足下列条件时，我们称其为湍流子数组：
 * 
 * 
 * 若 i <= k < j，当 k 为奇数时， A[k] > A[k+1]，且当 k 为偶数时，A[k] < A[k+1]；
 * 或 若 i <= k < j，当 k 为偶数时，A[k] > A[k+1] ，且当 k 为奇数时， A[k] < A[k+1]。
 * 
 * 
 * 也就是说，如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组。
 * 
 * 返回 A 的最大湍流子数组的长度。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：[9,4,2,10,7,8,8,1,9]
 * 输出：5
 * 解释：(A[1] > A[2] < A[3] > A[4] < A[5])
 * 
 * 
 * 示例 2：
 * 
 * 输入：[4,8,12,16]
 * 输出：2
 * 
 * 
 * 示例 3：
 * 
 * 输入：[100]
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= A.length <= 40000
 * 0 <= A[i] <= 10^9
 * 
 * 
 */
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
// @lc code=start

int Max(int a, int b)
{
    return a>b?a:b;
}

int isTurbu(int *arr, int i)
{
    if (arr[i-2] > arr[i-1] && arr[i-1] < arr[i])
    {
        return 1;
    }

    if (arr[i-2] < arr[i-1] && arr[i-1] > arr[i])
    {
        return 1;
    }
    return 0;  
}

int maxTurbulenceSize(int* arr, int arrSize){
    int maxlen = 0;
    int len = 0;
    if (arrSize <= 1)
    {
        return arrSize;
    }
    
    for (int i = 0; i < arrSize; i++)
    {
        if (i>=2 && isTurbu(arr, i))
        {
            len++;
        }        
        else if (i>=1 && arr[i] != arr[i-1])
        {
            len = 2;
        }
        else
        {
            len = 1;
        }
        maxlen = Max(maxlen,len);   
    }
    return maxlen;  
}

// @lc code=end
int array[]={4,8,12,16};
int main(void)
{
    int p = 0;
    p = maxTurbulenceSize(array, sizeof(array)/sizeof(array[0]));
    return 0;
}


int maxTurbulenceSize(int* arr, int arrSize){
    if (arrSize < 2)
    {
        return arrSize;
    }
    int maxlen = 0;
    //if (arrSize == 2)
    {
        if(arr[0]!=arr[1]) //没有考虑2个值相等的情况
        {
            maxlen = 2;
        }
        else
        {
            maxlen = 1;
        }
    }
    
    int right = 1;
    int left = 0;
    long dir = 0; // 0表示升序 1表示降序
    long dir2 = 0;
    //int maxlen = (arr[0]==arr[1]?1:2); //没有考虑三个100的情况
    while (right < arrSize-1)
    {
        dir = (arr[right-1]-arr[right]); // 没有注意到值可能会超出范围
        dir2 = (arr[right]-arr[right+1]);
        if (dir*dir2 >= 0)
        {
            left=right;
            right = left+1;
            continue;
        }
        right++;
        maxlen = Max(maxlen, right-left+1);
    }
    return maxlen;
}