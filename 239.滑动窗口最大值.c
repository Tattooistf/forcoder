/*
 * @lc app=leetcode.cn id=239 lang=c
 *
 * [239] 滑动窗口最大值
 *
 * https://leetcode-cn.com/problems/sliding-window-maximum/description/
 *
 * algorithms
 * Hard (47.79%)
 * Likes:    451
 * Dislikes: 0
 * Total Accepted:    61.1K
 * Total Submissions: 126.4K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * 给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
 * 个数字。滑动窗口每次只向右移动一位。
 * 
 * 返回滑动窗口中的最大值。
 * 
 * 
 * 
 * 进阶：
 * 
 * 你能在线性时间复杂度内解决此题吗？
 * 
 * 
 * 
 * 示例:
 * 
 * 输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
 * 输出: [3,3,5,5,6,7] 
 * 解释: 
 * 
 * ⁠ 滑动窗口的位置                最大值
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 * ⁠1 [3  -1  -3] 5  3  6  7       3
 * ⁠1  3 [-1  -3  5] 3  6  7       5
 * ⁠1  3  -1 [-3  5  3] 6  7       5
 * ⁠1  3  -1  -3 [5  3  6] 7       6
 * ⁠1  3  -1  -3  5 [3  6  7]      7
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 1 <= k <= nums.length
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start
// 无论是第一种Heap解题方式，还是第二种单调栈解题方式，都是维护首节点是最大值的结构

// 第二种解题思路：单调栈，需要加上栈底老化；实际上也是单调队列、优先级队列（思想类似）
static int *g_Stack = NULL;
static int g_Count = 0;
static int g_Start = 0;
void CreateStack(int size)
{
    g_Stack = (int*)malloc(sizeof(int)*size);
    memset(g_Stack,0,sizeof(int)*size);
    g_Count = 0;
    g_Start = 0;
    return;
}
void DestroyStack(void)
{
    if (g_Stack != NULL)
    {
        free(g_Stack);
    }
    g_Stack = NULL;
    g_Count = 0;
    g_Start = 0;
    return;
}
void StackPush(int val)
{
    g_Stack[g_Start+g_Count++] = val;
    return;
}
int StackPop(void)
{
    int res = g_Stack[--g_Count+g_Start];
    return res;
}
int StackPopBack(void)
{
    int res = g_Stack[g_Start++];
    g_Count--;
    return res;
}
int StackEmpty(void)
{
    return (g_Count == 0)?1:0;
}
int StackBottom(void)
{
    return g_Stack[g_Start];
}
int StackTop(void)
{
    return g_Stack[g_Start+g_Count-1];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    int idx = 0;
    if (numsSize == 0 || k == 0 || nums == NULL)
    {
        *returnSize = 0;
        return nums;
    }
    int *res = (int*)malloc(sizeof(int)*(numsSize-k+1));
    memset(res,0,sizeof(int)*(numsSize-k+1));
    CreateStack(numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        while (!StackEmpty() && nums[StackTop()]<=nums[i]) // 判断左边界情况；第二次坑忘记判断Heap是否为空
        {
            StackPop();
        }
        StackPush(i);

        if (i>=k-1)
        {
            while (!StackEmpty() && StackBottom()<=(i-k))
            {
                StackPopBack();
            }
            res[idx++] = nums[StackBottom()];
        }
    }
    DestroyStack();
    *returnSize = idx;
    return res;
}
// @lc code=end

int main(void)
{
    int nums[] = {1,-1};
    int k = 1;
    int *res = NULL;
    int cnt = 0;
    res = maxSlidingWindow(nums,sizeof(nums)/sizeof(nums[0]),k,&cnt);
    return 0;
}


// 第一种解题方法，堆的方式，花了接近2个小时；最关键在于
// 没有搞明白如何删除左侧出窗口的值，看答案后才找到一种方法：存储下标，Heap头的下标超过窗口左侧就出Heap
static int *g_Heap = NULL;
static int g_Size = 0;
void CreateHeap(int k)
{
    g_Heap = (int*)malloc(sizeof(int)*(k+1)); // 无意识在前面加了int*导致g_Heap为空，调试半天
    memset(g_Heap,0,sizeof(int)*(k+1));
    g_Size  =0;
    return;
}
void DestroyHeap(void)
{
    if (g_Heap != NULL)
    {
        free(g_Heap);
    }
    g_Size = 0;
    g_Heap = NULL;
    
    return;
}
void PushHeap(int *nums,int val) //建立大堆
{
    g_Heap[++g_Size] = val;
    int i;
    for (i = g_Size; (i>>1) >= 1; i=i>>1)
    {
        if (nums[g_Heap[i>>1]] < nums[val])
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
int PopHeap(int *nums)
{
    int res = g_Heap[1];
    int tmp = g_Heap[g_Size];
    g_Size--;
    int i = 1;
    int j = 1;
    for (i = 1; 2*i <= g_Size; i=j)
    {
        if ((2*i+1)<=g_Size && nums[g_Heap[2*i]]<nums[g_Heap[2*i+1]])
        {
            j = 2*i+1;
        }
        else
        {
            j = 2*i;
        }
        if (nums[g_Heap[j]]>nums[tmp])
        {
            g_Heap[i] = g_Heap[j];
        }
        else
        {
            break;
        }
        i=j;
    }
    g_Heap[i] = tmp;
    
    return res;
}
int HeapEmpty(void)
{
    return (g_Size == 0)?1:0;
}

int HeapTop(void)
{
    return g_Heap[1];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    int idx = 0;
    if (numsSize == 0 || k == 0 || nums == NULL)
    {
        *returnSize = 0;
        return nums;
    }
    int *res = (int*)malloc(sizeof(int)*(numsSize-k+1));
    memset(res,0,sizeof(int)*(numsSize-k+1));
    CreateHeap(numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        PushHeap(nums,i);
        if (i>=k-1)
        {
            while (!HeapEmpty() && HeapTop()<=(i-k)) // 判断左边界情况；第二次坑忘记判断Heap是否为空
            {
                PopHeap(nums);
            }
            res[idx++] = nums[HeapTop()];
        }
    }  

    DestroyHeap();
    *returnSize = idx;
    return res;
}

// 第三种解题思路：动态规划，看解题答案是比较简单的
#define MAX(a,b) ((a)>(b)?(a):(b))
int GetMax(int *nums,int start,int len,int max)
{
    if (nums[start] != max)
    {
        return max;
    }
    int res = nums[start+1];
    for (int i = start+2; i < start+len; i++) // 栽坑一次：直接使用了len，应该是start+len
    {
        if (nums[i] == max)
        {
            return max;
        }
        if (nums[i]>res)
        {
            res = nums[i];
        }
    }
    return res;
}
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    if (nums == NULL || numsSize == 0 || k == 0)
    {
        *returnSize = 0;
        return nums;
    }
    int *res = (int*)malloc(sizeof(int)*(numsSize-k+1));
    memset(res,0,sizeof(int)*(numsSize-k+1));
    int tmp = 0;
    int max = nums[0];
    for (int i = 1; i <= k-1; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }
    }
    res[0] = max;
    for (int i = k; i < numsSize; i++)
    {
        tmp = GetMax(nums,i-k,k,max);// 原始区间扣除窗口左侧第一个值之后的最大值
        max = MAX(tmp,nums[i]);
        res[i-k+1] = max;
    }
    *returnSize = numsSize-k+1;
    return res;
}