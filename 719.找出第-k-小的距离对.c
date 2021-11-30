/*
 * @lc app=leetcode.cn id=719 lang=c
 *
 * [719] 找出第 k 小的距离对
 *
 * https://leetcode-cn.com/problems/find-k-th-smallest-pair-distance/description/
 *
 * algorithms
 * Hard (35.30%)
 * Likes:    196
 * Dislikes: 0
 * Total Accepted:    8.7K
 * Total Submissions: 23.7K
 * Testcase Example:  '[1,3,1]\n1'
 *
 * 给定一个整数数组，返回所有数对之间的第 k 个最小距离。一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值。
 * 
 * 示例 1:
 * 
 * 
 * 输入：
 * nums = [1,3,1]
 * k = 1
 * 输出：0 
 * 解释：
 * 所有数对如下：
 * (1,3) -> 2
 * (1,1) -> 0
 * (3,1) -> 2
 * 因此第 1 个最小距离的数对是 (1,1)，它们之间的距离为 0。
 * 
 * 
 * 提示:
 * 
 * 
 * 2 <= len(nums) <= 10000.
 * 0 <= nums[i] < 1000000.
 * 1 <= k <= len(nums) * (len(nums) - 1) / 2.
 * 
 * 
 */

// @lc code=start

// 二分法参考：
int cmpmax(void *a, void *b)
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

int func(int *arr, int size,int val)
{
    int j = 0;
    int count = 0;
    for (int i = 0; i < size; i++) // 等同一个滑动窗口
    {
        while (arr[i]-arr[j] > val)
        {
            j++;
        }
        count += i-j;
    }
    
    return count;
}

int smallestDistancePair(int* nums, int numsSize, int k){
    qsort(nums,numsSize,sizeof(int),cmpmax);
    int left = 0;
    int right = nums[numsSize-1];

    while (left < right)
    {
        int mid = left+(right-left)/2;
        if (func(nums,numsSize,mid) >= k)
        {
            right = mid;
        }
        else
        {
            left = mid+1;
        }
    }
    return left;
}
// @lc code=end



int *g_Heap = NULL;
int g_Max = 0;
int g_Size = 0;
void InitHeap(int size)
{
    g_Heap = (int *)malloc(sizeof(int)*(size+1));
    // memset(g_Heap,0,sizeof(int)*(size+1));
    g_Max = size;
    g_Size = 0;
    return;
}
void DestoryHeap(void)
{
    if (g_Heap)
    {
        free(g_Heap);
    }
    g_Heap = NULL;
    g_Size = 0;
    return;
}
void HeapPush(int val)
{
    g_Heap[++g_Size] = val;
    int i = 1;
    for (i = g_Size; i/2 >= 1; i=i>>1)
    {
        if (g_Heap[i>>1] < val)
        {
            g_Heap[i] = g_Heap[i>>1];
        }
        else
        {
            break;
        }
    }
    g_Heap[i] = val; // 错误：误放到for里面了，实际应该在外面
    return;
}

int HeapPop(void)
{
    int tmp = g_Heap[1];
    int val = g_Heap[g_Size--];

    int j = 1;
    int i = 1;
    for (i = 1; 2*i <= g_Size; i=j)
    {
        if (2*i+1 <= g_Size && g_Heap[2*i] < g_Heap[2*i+1])
        {
            j = 2*i+1;
        }
        else
        {
            j = 2*i;
        }
        
        if (g_Heap[j] > val)
        {
            g_Heap[i] = g_Heap[j];
        }
        else
        {
            break;
        }
    }
    g_Heap[i] = val;
    return tmp;
}

int HeapTop(void)
{
    return g_Heap[1];
}

int cmpmax(void *a, void *b)
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

// 堆解题，16/19，超时无法全部通过
int smallestDistancePair(int* nums, int numsSize, int k){
    qsort(nums,numsSize,sizeof(int),cmpmax);
    InitHeap(k+1);

    int count = 0;
    for (int i = 0; i < numsSize; i++) // 错误：前面错误使用k，最保险使用numsSize
    {
        for (int j = i+1; j < numsSize; j++)
        {
            HeapPush(nums[j]-nums[i]);
            count++;
            if (count > k)
            {
                HeapPop();
            }
        }
    }
    int ret = HeapTop();
    DestoryHeap();
    return ret;
}