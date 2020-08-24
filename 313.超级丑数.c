/*
 * @lc app=leetcode.cn id=313 lang=c
 *
 * [313] 超级丑数
 *
 * https://leetcode-cn.com/problems/super-ugly-number/description/
 *
 * algorithms
 * Medium (62.98%)
 * Likes:    97
 * Dislikes: 0
 * Total Accepted:    9.4K
 * Total Submissions: 14.9K
 * Testcase Example:  '12\n[2,7,13,19]'
 *
 * 编写一段程序来查找第 n 个超级丑数。
 * 
 * 超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。
 * 
 * 示例:
 * 
 * 输入: n = 12, primes = [2,7,13,19]
 * 输出: 32 
 * 解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12
 * 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
 * 
 * 说明:
 * 
 * 
 * 1 是任何给定 primes 的超级丑数。
 * 给定 primes 中的数字以升序排列。
 * 0 < k ≤ 100, 0 < n ≤ 10^6, 0 < primes[i] < 1000 。
 * 第 n 个超级丑数确保在 32 位有符整数范围内。
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
// @lc code=start
// 第一种方法，使用heap处理，但不太好解决重复值的问题
int *g_Heap = NULL;
int g_Size = 0;
void CreateHeap(int size)
{
    g_Heap = (int *)malloc(sizeof(int)*(size+1));
    memset(g_Heap,0,sizeof(int)*(size+1));
    g_Size = 0;
    return;
}

void DestroyHeap(void)
{
    if (g_Heap != NULL)
    {
        free(g_Heap);
    }
    g_Size = 0;
    
    return;
}

void PushHeap(int val)
{
    g_Heap[++g_Size] = val;
    int i = g_Size;
    for (i = g_Size; (i>>1) >= 1; i = i>>1)
    {
        if (g_Heap[i>>1] > val)
        {
            g_Heap[i] = g_Heap[i>>1];
        }
        else
        {
            break;
        }
        
    }
    g_Heap[i] = val;
    
    return;
}

int PopHeap(void)
{
    int res = g_Heap[1];
    int val = g_Heap[g_Size];
    g_Size--;
    int i = 1;
    int j = 1;
    for (i = 1; 2*i <= g_Size; i=j)
    {
        if ((2*i+1)<=g_Size && (g_Heap[2*i] > g_Heap[2*i+1]))
        {
            j = 2*i+1;
        }
        else
        {
            j = 2*i;
        }

        if (g_Heap[j] < val)
        {
            g_Heap[i] = g_Heap[j];
        }
        else
        {
            break;
        }
    }
    g_Heap[i] = val;
        
    return res;
}

int TopHeap(void)
{
    return g_Heap[1];
}

#define INT_MAX 0x7fffffffUL

int nthSuperUglyNumber(int n, int* primes, int primesSize){
    int count = 0;
    while (count<n)
    {
        count++;
        int val = PopHeap();
        while (TopHeap() == val)
        {
            (void)PopHeap();
        }
        
        for (int i = 0; i < primesSize; i++)
        {
            int new = val*primes[i];
            if (new > INT_MAX || IsUsed(new))
            {
                continue;
            }
            PushHeap(new);
        }
        
    }
    return PopHeap();
}


// @lc code=end


// 解法二：采用每次计算最小值的方式，引入index标注每个prime当前运算的res位置
#define INT_MAX 0x7fffffffUL

int nthSuperUglyNumber(int n, int* primes, int primesSize){
    int count = 0;
    if (n == 1)
    {
        return 1;
    }
    // index表示每个primes当前乘到res的哪个位置
    int *index = (int *)malloc(sizeof(int)*primesSize);
    memset(index,0,sizeof(int)*primesSize);
    
    int *res = (int *)malloc(sizeof(int)*n);
    memset(res,0,sizeof(int)*n); // 第一次栽坑 拷贝使用的index忘记修改为res
    res[count++] = 1;
    
    while (count < n)
    {
        int min = INT_MAX; // 第二次栽坑：没有注意最小值的循环起始都应该归零
        int id = 0;
        for (int i = 0; i < primesSize; i++)
        {
            int new = primes[i] * res[index[i]];
            if (new < min)
            {
                min = new;
                id = i;
            }
            else if (new == min)
            {
                index[i]++;
            } 
        }
        res[count++] = min;
        // printf("index %d:%d\n",count-1,min);
        index[id]++;
    }

    int result = res[n-1];
    free(res);
    free(index);
    return result;
}
