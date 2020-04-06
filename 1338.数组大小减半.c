/*
 * @lc app=leetcode.cn id=1338 lang=c
 *
 * [1338] 数组大小减半
 *
 * https://leetcode-cn.com/problems/reduce-array-size-to-the-half/description/
 *
 * algorithms
 * Medium (61.94%)
 * Likes:    6
 * Dislikes: 0
 * Total Accepted:    3K
 * Total Submissions: 4.8K
 * Testcase Example:  '[3,3,3,3,5,5,5,2,2,7]'
 *
 * 给你一个整数数组 arr。你可以从中选出一个整数集合，并删除这些整数在数组中的每次出现。
 * 
 * 返回 至少 能删除数组中的一半整数的整数集合的最小大小。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：arr = [3,3,3,3,5,5,5,2,2,7]
 * 输出：2
 * 解释：选择 {3,7} 使得结果数组为 [5,5,5,2,2]、长度为 5（原数组长度的一半）。
 * 大小为 2 的可行集合有 {3,5},{3,2},{5,2}。
 * 选择 {2,7} 是不可行的，它的结果数组为 [3,3,3,3,5,5,5]，新数组长度大于原数组的二分之一。
 * 
 * 
 * 示例 2：
 * 
 * 输入：arr = [7,7,7,7,7,7]
 * 输出：1
 * 解释：我们只能选择集合 {7}，结果数组为空。
 * 
 * 
 * 示例 3：
 * 
 * 输入：arr = [1,9]
 * 输出：1
 * 
 * 
 * 示例 4：
 * 
 * 输入：arr = [1000,1000,3,7]
 * 输出：1
 * 
 * 
 * 示例 5：
 * 
 * 输入：arr = [1,2,3,4,5,6,7,8,9,10]
 * 输出：5
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= arr.length <= 10^5
 * arr.length 为偶数
 * 1 <= arr[i] <= 10^5
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start
// 几种思想全部错误：
// 1、排序后计算left和right的数目，取最小值
// 2、计算重复的个数，总数的一半减去重复的个数；可是当重复个数超过一半的时候，无解
// 3、只能想到最原始的解法，按重复次数从高到底排序，结果是超时;最终使用qsort优化解决超时问题

#define MAX (100002) //最大值不能直接作为下标，需要预留max+1
int cmpmax(const void* a,const void* b)
{
    return *((int*)a)<*((int*)b)?1:0;
}

int minSetSize(int* arr, int arrSize){
    int count=0;
    if (arr==NULL || arrSize==0)
    {
        return 0;
    }
    //排序从小到大后遍历到中间位置不重复的数字个数就是最小集合数
    int *array=(int *)malloc(MAX*sizeof(arr[0]));
    memset(array,0,MAX*sizeof(arr[0]));
    for (int i = 0; i < arrSize; i++)
    {
        array[arr[i]]++;
    }

    for (int i = 0; i < MAX; i++)
    {
        if(array[i]==0) continue;
        array[count++]=array[i];
    }
    
    qsort(array,count,sizeof(int),cmpmax);
    int sum=0;
    for (int i = 0; i < count; i++)
    {
        sum+=array[i];
        if(sum>=(arrSize>>1)) return i+1;//需要释放内存
    }
    free(array);
    return count;
}

// @lc code=end

int minSetSize1(int* arr, int arrSize){
    int count=1;
    if (arr==NULL || arrSize==0)
    {
        return 0;
    }
    //排序从小到大后遍历到中间位置不重复的数字个数就是最小集合数
    for (int i = 0; i < arrSize; i++)
    {
        for (int j = i+1; j < arrSize; j++)
        {
            if (arr[i]>arr[j])
            {
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    //从前到中间位置遍历，如果不重复就表示集合数+1
    int countleft=1;
    int countright=1;
    for (int i = 1; i < arrSize; i++)
    {   
        if (arr[i]!=arr[i-1])
        {
            if (i<(arrSize>>1))
            {
                countleft++;
            }
            count++;
        }
    }
    int temp=(arrSize>>1)-(arrSize-count);
    if (temp>0)
    {
        return temp;
    }
    
    if (count==countleft)
    {
        return 1;
    }
    countright=count-countleft;
    
    return (countright<countleft)?countright:countleft;    
}


int main(void)
{
    int array[]={9,77,63,22,92,9,14,54,8,38,18,19,38,68,58,19};
    int ret=0;
    ret = minSetSize(array,sizeof(array)/sizeof(array[0]));
    return 0;
}

