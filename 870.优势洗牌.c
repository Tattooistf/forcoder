/*
 * @lc app=leetcode.cn id=870 lang=c
 *
 * [870] 优势洗牌
 *
 * https://leetcode-cn.com/problems/advantage-shuffle/description/
 *
 * algorithms
 * Medium (40.31%)
 * Likes:    132
 * Dislikes: 0
 * Total Accepted:    11.9K
 * Total Submissions: 28.8K
 * Testcase Example:  '[2,7,11,15]\n[1,10,4,11]'
 *
 * 给定两个大小相等的数组 A 和 B，A 相对于 B 的优势可以用满足 A[i] > B[i] 的索引 i 的数目来描述。
 * 
 * 返回 A 的任意排列，使其相对于 B 的优势最大化。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：A = [2,7,11,15], B = [1,10,4,11]
 * 输出：[2,11,7,15]
 * 
 * 
 * 示例 2：
 * 
 * 输入：A = [12,24,8,32], B = [13,25,32,11]
 * 输出：[24,32,8,12]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= A.length = B.length <= 10000
 * 0 <= A[i] <= 10^9
 * 0 <= B[i] <= 10^9
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int cmp(const void* a, const void *b)
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

int cmp2(const void* a, const void *b)
{
    int *tmpa = *((int **)a);
    int *tmpb = *((int **)b);
    if (tmpa[0] < tmpb[0])
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int* advantageCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int *ret = (int*)malloc(nums1Size*sizeof(int));
    memset(ret, 0, nums1Size*sizeof(int));
    qsort(nums1,nums1Size,sizeof(int),cmp);
    int **newNums = (int **)malloc(nums2Size*sizeof(int *));
    for (int i = 0; i < nums2Size; i++)
    {
        newNums[i] = (int *)malloc(sizeof(int)*2);
        newNums[i][0] = nums2[i];
        newNums[i][1] = i; /* 记录原先的位置 */
    }
    qsort(newNums,nums2Size,sizeof(int*),cmp2);
    int right = nums2Size - 1;
    for (int i = 0,j = 0; i < nums2Size; i++)
    {
        if (nums1[i] > newNums[j][0])
        {
            ret[newNums[j][1]] = nums1[i];
            //i++;
            j++;
        }
        else
        {
            ret[newNums[right][1]] = nums1[i];
            //i++;
            right--;
        }   
    }
    // 此处需要释放newNums的内存
    *returnSize = nums1Size;
    return ret;
}
// @lc code=end

int main()
{
    int A[] = {2,7,11,15};
    int B[] = {1,10,4,11};
    int size = 0;
    int *res = advantageCount(A,sizeof(A)/sizeof(A[0]),B,sizeof(B)/sizeof(B[0]), &size);
    return 0;
}

/* 思路基本正确：想到贪心法和二分法，但不是最优的 */
int binsearch(int *nums, int val,int size)
{
    int start = 0;
    int end = size; /* 忘记了end初始化，最开始用的0导致出错 */
    while (start < end)
    {
        int mid = start + (end-start)/2;
        if (nums[mid] > val)
        {
            end = mid;
        }
        else
        {
            start = mid+1;
        }
    }
    return start;    
}

int cmp(const void *a, const void *b)
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

int* advantageCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int *ret = (int *)malloc(sizeof(int)*nums1Size);
    int *used = (int *)malloc(sizeof(int)*nums1Size);
    memset(ret, 0, sizeof(int)*nums1Size);
    memset(used, 0, sizeof(int)*nums1Size);

    int point = 0;
    qsort(nums1, nums1Size, sizeof(int),cmp);
    for (int i = 0; i < nums2Size; i++)
    {
        int nearly = binsearch(nums1,nums2[i],nums1Size);
        for (int i = 0; i < nums1Size; i++)
        {
            int psz = (nearly+i)%nums1Size; /* 当从小到大没有找到时从最小处填写 */
            if (used[psz] == 0)
            {
                ret[point++] = nums1[psz];
                used[psz] = 1;
                break; /* 忘记break，导致出错 */
            }
        }
    }
    *returnSize = nums1Size;
    free(used);
    used = NULL;
    return ret;
}