/*
 * @lc app=leetcode.cn id=862 lang=c
 *
 * [862] 和至少为 K 的最短子数组
 *
 * https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/description/
 *
 * algorithms
 * Hard (12.83%)
 * Likes:    114
 * Dislikes: 0
 * Total Accepted:    5K
 * Total Submissions: 37.5K
 * Testcase Example:  '[1]\n1'
 *
 * 返回 A 的最短的非空连续子数组的长度，该子数组的和至少为 K 。
 * 
 * 如果没有和至少为 K 的非空子数组，返回 -1 。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：A = [1], K = 1
 * 输出：1
 * 
 * 
 * 示例 2：
 * 
 * 输入：A = [1,2], K = 4
 * 输出：-1
 * 
 * 
 * 示例 3：
 * 
 * 输入：A = [2,-1,2], K = 3
 * 输出：3
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= A.length <= 50000
 * -10 ^ 5 <= A[i] <= 10 ^ 5
 * 1 <= K <= 10 ^ 9
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include "math.h"
// @lc code=start

// 第二次使用前缀和暴力破解 83/93，时间超时，
int shortestSubarray(int* A, int ASize, int K){
    long long sum=0;
    int res=ASize;
    int flag=0;

    if (A==NULL || ASize<1)
    {
        return -1;
    }
    int *presum=(int *)malloc(sizeof(int)*ASize);
    // 计算前缀和
    for (int i = 0; i < ASize; i++)
    {
        sum+=A[i];
        presum[i]=sum;
    }
    // 比较每一个前缀和，判断是否有最小大于K的情况
    for (int i = 0; i < ASize; i++)
    {
        if (presum[i]>=K)//本身的sum也需要治疗
        {
            flag=1;
            res=res>(i+1)?(i+1):res;
        }
        
        for (int j = i+1; j < ASize; j++)
        {
            if (presum[j]-presum[i]>=K)
            {
                flag=1;
                res=res>(j-i)?(j-i):res;
            }
            
        }
    }
    res=(flag<1)?-1:res;
    free(presum);
    presum=NULL;
    return res;
}


// @lc code=end

int main(void)
{
    int array[]={77,19,35,10,-14};
    int sum=19;
    int len=0;
    len=shortestSubarray(array,sizeof(array)/sizeof(array[0]),sum);
    printf("%d\n",len);

    return 0;
}


// 第一次解题直接尝试使用滑动窗口
int shortestSubarray2(int* A, int ASize, int K){
    long long sum=0;
    int left=0,right=0;
    int res=ASize;
    int flag=0;

    if (A==NULL || ASize<1)
    {
        return res;
    }

    while (A[left]<0)
    {
        left++;
        right++;
    }
    
    while (1)
    {
        if (right>=ASize || left>=ASize)
        {
            break;
        }
        
        if (sum<K)
        {
            if ((A[left]<0) && (left<right))
            {
                sum-=A[left++];
            }
            else
            {
                sum+=A[right++];
            }           
        }
        else
        {
            flag=1;//表示找到一个解
            res=res<(right-left)?res:(right-left);
            sum-=A[left];
            left++;
        } 
    }

    while (left<right)
    {
        if(sum>=K)
        {
            flag=1;            
            res=res<(right-left)?res:(right-left);
        }
        sum-=A[left];
        left++;
    }
    
    if (flag==0)
    {
        return -1;
    }
    return res;
}

