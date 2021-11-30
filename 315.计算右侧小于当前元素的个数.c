/*
 * @lc app=leetcode.cn id=315 lang=c
 *
 * [315] 计算右侧小于当前元素的个数
 *
 * https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/description/
 *
 * algorithms
 * Hard (42.16%)
 * Likes:    647
 * Dislikes: 0
 * Total Accepted:    50.1K
 * Total Submissions: 119.8K
 * Testcase Example:  '[5,2,6,1]'
 *
 * 给你`一个整数数组 nums ，按要求返回一个新数组 counts 。数组 counts 有该性质： counts[i] 的值是  nums[i]
 * 右侧小于 nums[i] 的元素的数量。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [5,2,6,1]
 * 输出：[2,1,1,0] 
 * 解释：
 * 5 的右侧有 2 个更小的元素 (2 和 1)
 * 2 的右侧仅有 1 个更小的元素 (1)
 * 6 的右侧有 1 个更小的元素 (1)
 * 1 的右侧有 0 个更小的元素
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [-1]
 * 输出：[0]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [-1,-1]
 * 输出：[0,0]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
// @lc code=start


// 考虑使用归并排序求解，很多类似的场景都用到了归并排序
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void domerge(int **arr, int left, int boud, int right, int *count)
{
    int num = 0;
    int i = left;
    int j = boud+1;
    int **ret = (int **)malloc(sizeof(int*)*(right-left+1));
    while (i <= boud && j <= right)
    {
        if (arr[i][0] <= arr[j][0])
        {
            ret[num++] = arr[i];
            count[arr[i][1]] += j-boud-1;
            i++;
        }
        else
        {
            ret[num++] = arr[j];
            j++;
        }
    }

    while (i <= boud) // 异常是这个地方误用<，应该用<=，异常原因是赋值不全，导致后面free的时候有重复释放
    {
        count[arr[i][1]] += j-boud-1; // j已经属于j++，所以不需要再+1
        ret[num++] = arr[i++];
    }

    while (j <= right)
    {
        ret[num++] = arr[j++];
    }
    
    for (int i = 0; i < num; i++)
    {
        arr[left+i] = ret[i];
    }
    free(ret);
    
    return;
}

void merge(int **arr, int left, int right, int *count)
{
    if (left >= right)
    {
        return;
    }
    
    int mid = left+(right-left)/2;

    merge(arr,left,mid,count);
    merge(arr,mid+1,right,count);
    domerge(arr,left,mid,right,count);
    return;
}

int* countSmaller(int* nums, int numsSize, int* returnSize){
    int *ret = (int*)malloc(sizeof(int)*numsSize);
    int **arr = (int **)malloc(sizeof(int*)*numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        arr[i] = (int *)malloc(sizeof(int)*2);
        arr[i][0] = nums[i];
        arr[i][1] = i;

        ret[i] = 0;
    }
    
    merge(arr, 0, numsSize-1, ret);

    for (int i = 0; i < numsSize; i++)
    {
        free(arr[i]);
    }
    free(arr);
    
    *returnSize = numsSize;
    return ret;
}
// @lc code=end

int main(void)
{
    int arr[] = {5,2,6,1};
    int* ptr = NULL;
    int cnt = 0;
    ptr = countSmaller(arr, sizeof(arr)/sizeof(arr[0]), &cnt);

    return 0;
}

#if 0
// 居然没有想起来排序的做法,用例进行加固，62/65，无法完全通过
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
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

void insert(int *arr, int size, int index, int val)
{
    if (size == 0)
    {
        arr[index] = val;
        return;
    }
    
    for (int i = size-1; i >= index; i--)
    {
        arr[i+1] = arr[i];
    }
    arr[index] = val;
    return;
}

int* countSmaller(int* nums, int numsSize, int* returnSize){
    int *ret = (int*)malloc(sizeof(int)*numsSize);
    int *sort = (int *)malloc(sizeof(int)*numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        sort[i] = 0xFFFFFFFF;
    }
    int count = 0;
    for (int i = numsSize-1; i >= 0; i--) // 错误：前面漏修改了，使用i++
    {
        int left = 0;
        int right = count;
        while (left < right)
        {
            int mid = left+(right-left)/2;
            if (nums[i] > sort[mid])
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            }
        }
        ret[i] = left;
        insert(sort,count,left,nums[i]);
        count++;
    }

    *returnSize = numsSize;
    return ret;
}

// 还是超时 63/65，感觉主要还是插入法导致超时的
int* countSmaller(int* nums, int numsSize, int* returnSize){
    int *ret = (int*)malloc(sizeof(int)*numsSize);
    int left = 0;
    int right = 0;

    int count = 0;
    ret[numsSize-1] = 0;
    for (int i = numsSize-2; i >= 0; i--) // 错误：前面漏修改了，使用i++
    {
        // qsort(nums+i+1, numsSize-i-1,sizeof(int),cmpmax);
        left = i+1;
        right = numsSize;
        while (left < right)
        {
            int mid = left+(right-left)/2;
            if (nums[i] > nums[mid])
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            }
        }
        // printf("left %d\n",left);
        ret[i] = left-1-i;
        // ret[count++] = left-i-1; // 错误：前面搞错了使用的是left
        int tmp = nums[i];
        for (int k = i; k < left && k < numsSize-1; k++)
        {
            nums[k] = nums[k+1];
        }
        nums[left-1] = tmp; // 错误：前面使用的是left
    }

    // 直接使用ret[i]就不需要颠倒数组
    // for (int i = 0; i < count/2; i++)
    // {
    //     int tmp = ret[i];
    //     ret[i] = ret[numsSize-1-i];
    //     ret[numsSize-1-i] = tmp;
    // }
    
    *returnSize = numsSize;
    return ret;
}

// 暴力求解法：肯定时间超限，通过90%左右，57/65
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int* nums, int numsSize, int* returnSize){
    int *ret = (int*)malloc(sizeof(int)*numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        int cnt = 0;
        for (int j = i+1; j < numsSize; j++)
        {
            if (nums[j] < nums[i])
            {
                cnt++;
            }
        }
        ret[i] = cnt;
    }
    *returnSize = numsSize;
    return ret;
}
#endif