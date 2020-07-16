/*
 * @lc app=leetcode.cn id=215 lang=c
 *
 * [215] 数组中的第K个最大元素
 *
 * https://leetcode-cn.com/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (62.61%)
 * Likes:    612
 * Dislikes: 0
 * Total Accepted:    169.1K
 * Total Submissions: 262.4K
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * 在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 * 
 * 示例 1:
 * 
 * 输入: [3,2,1,5,6,4] 和 k = 2
 * 输出: 5
 * 
 * 
 * 示例 2:
 * 
 * 输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
 * 输出: 4
 * 
 * 说明: 
 * 
 * 你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。
 * 
 */

// @lc code=start

/*
 * 基本上再写一边堆排序，下标和比较条件犹豫了一会，修改正确后一次通过
 * 32/32 cases passed (4 ms)
 * Your runtime beats 99.84 % of c submissions
 * Your memory usage beats 100 % of c submissions (5.9 MB)
 */
static int* g_Heap = NULL;
static int g_Size = 0;

void CreateHeap(int k)
{
    g_Heap = (int*)malloc((k+1)*sizeof(int));
    memset(g_Heap,0,(k+1)*sizeof(int));
    g_Size = 0;
    return;
}
void DestoryHeap(void)
{
    free(g_Heap);
    g_Heap = NULL;
    g_Size = 0;
    return;
}

void PushHeap(int val)
{
    g_Heap[++g_Size] = val; // 差点栽坑，必须从1开始，所以是++X
    int i = 0;
    for (i = g_Size; i/2 >= 1; i=i>>1)
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
    int tmp = g_Heap[g_Size];
    g_Size--;
    int i = 0;
    int j = 0;
    for ( i = 1; 2*i <= g_Size; i = j)
    {
        if ((2*i+1) <= g_Size && g_Heap[2*i] > g_Heap[2*i+1])
        {
            j = 2*i + 1;
        }
        else
        {
            j = 2*i;
        }
        if (tmp > g_Heap[j])
        {
            g_Heap[i] = g_Heap[j];
        }
        else
        {
            break;
        }
        i = j;
    }
    g_Heap[i] = tmp;

    return res;
}
int TopHeap(void)
{
    return g_Heap[1];
}
// 解法二：最小堆解法
int findKthLargest(int* nums, int numsSize, int k){
    CreateHeap(k);
    for (int i = 0; i < numsSize; i++)
    {
        if (i<k)
        {
            PushHeap(nums[i]);
            continue;
        }
        if (TopHeap()<nums[i])
        {
            PopHeap();
            PushHeap(nums[i]);
        }
    }
    int res = PopHeap();
    DestoryHeap();
    return res;
}


// @lc code=end
/*
 * 32/32 cases passed (24 ms)
 * Your runtime beats 38.36 % of c submissions
 * Your memory usage beats 6.25 % of c submissions (20.3 MB)
 */


void merge(int* array,int s,int m, int e) // 合并的算法没找到合适的，忘记了传m进来
{
    int *tmp = (int *)malloc(sizeof(int)*(e-s+1));
    int cnt = 0;
    int s1 = s;
    int m1 = m;
    int e1 = e;
    while (s1<m && m1<=e)
    {
        if (array[s1] < array[m1])
        {
            tmp[cnt++] = array[s1];
            s1++;
        }
        else
        {
            tmp[cnt++] = array[m1];
            m1++;
        }
    }
    while (s1<m)
    {
        tmp[cnt++] = array[s1++];
    }
    while (m1<=e)
    {
        tmp[cnt++] = array[m1++];
    }  
    memcpy(array+s,tmp,cnt*sizeof(int)); // 调试栽坑，size忘记*sizeof(int)了
    free(tmp);
    return;
}

void divmerge(int* array, int start, int end)
{
    if (start == end)
    {
        return;
    }
    
    int mid = (start+end)/2;
    divmerge(array,start,mid);
    divmerge(array,mid+1,end);
    merge(array,start,mid+1,end);
    
    return;
}
// 解法一：分裂合并法
int findKthLargest(int* nums, int numsSize, int k){
    divmerge(nums,0,numsSize-1);
    
    return nums[numsSize-k];
}

