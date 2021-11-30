/*
 * @lc app=leetcode.cn id=1345 lang=c
 *
 * [1345] 跳跃游戏 IV
 *
 * https://leetcode-cn.com/problems/jump-game-iv/description/
 *
 * algorithms
 * Hard (35.89%)
 * Likes:    60
 * Dislikes: 0
 * Total Accepted:    5.4K
 * Total Submissions: 14.7K
 * Testcase Example:  '[100,-23,-23,404,100,23,23,23,3,404]'
 *
 * 给你一个整数数组 arr ，你一开始在数组的第一个元素处（下标为 0）。
 * 
 * 每一步，你可以从下标 i 跳到下标：
 * 
 * 
 * i + 1 满足：i + 1 < arr.length
 * i - 1 满足：i - 1 >= 0
 * j 满足：arr[i] == arr[j] 且 i != j
 * 
 * 
 * 请你返回到达数组最后一个元素的下标处所需的 最少操作次数 。
 * 
 * 注意：任何时候你都不能跳到数组外面。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：arr = [100,-23,-23,404,100,23,23,23,3,404]
 * 输出：3
 * 解释：那你需要跳跃 3 次，下标依次为 0 --> 4 --> 3 --> 9 。下标 9 为数组的最后一个元素的下标。
 * 
 * 
 * 示例 2：
 * 
 * 输入：arr = [7]
 * 输出：0
 * 解释：一开始就在最后一个元素处，所以你不需要跳跃。
 * 
 * 
 * 示例 3：
 * 
 * 输入：arr = [7,6,9,6,9,6,9,7]
 * 输出：1
 * 解释：你可以直接从下标 0 处跳到下标 7 处，也就是数组的最后一个元素处。
 * 
 * 
 * 示例 4：
 * 
 * 输入：arr = [6,1,9]
 * 输出：2
 * 
 * 
 * 示例 5：
 * 
 * 输入：arr = [11,22,7,7,7,7,7,7,7,22,13]
 * 输出：3
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= arr.length <= 5 * 10^4
 * -10^8 <= arr[i] <= 10^8
 * 
 * 
 */

// @lc code=start

typedef struct Queue
{
    int *ptr;
    int rd;
    int wr;
    int cnt;
    int max;
}Queue;
Queue q;

void InitQueue(int size)
{
    q.ptr = (int*)malloc(sizeof(int)*size);
    memset(q.ptr,0,sizeof(int)*size);
    q.rd = 0;
    q.wr = 0;
    q.cnt = 0;
    q.max = size;
    return;
}

void DestoryQueue(void)
{
    if (q.ptr != NULL)
    {
        free(q.ptr);
    }
    q.rd = 0;
    q.wr = 0;
    q.max = 0;
    q.cnt = 0;
    return;
}

void enQueue(int val)
{
    if (q.cnt >= q.max)
    {
        return;
    }
    q.ptr[q.wr] = val;
    q.wr = (q.wr+1)%q.max;
    q.cnt++;
    return;
}

int deQueue(void)
{
    if (q.cnt <= 0)
    {
        return 0xFFFFFFFF;
    }
    int tmp = q.ptr[q.rd];
    q.rd = (q.rd+1)%q.max;
    q.cnt--;
    return tmp;
}

int Empty(void)
{
    return (q.cnt == 0);
}

int QueueCnt(void)
{
    return q.cnt;
}

#define INIT_MAX 0x0fffffff
#define MIN(a,b) ((a)>(b)?(b):(a))
int minJumps(int* arr, int arrSize){
    InitQueue(arrSize);
    int *step = (int *)malloc(sizeof(int)*arrSize);
    for (int i = 0; i < arrSize; i++)
    {
        step[i] = INIT_MAX;
    }

    int *visit = (int *)malloc(sizeof(int)*arrSize);
    memset(visit,0,sizeof(int)*arrSize);

    enQueue(arrSize-1);
    step[arrSize-1] = 0;
    while(!Empty())
    {
        int i = deQueue();
        if (i-1 >= 0 && step[i-1] == INIT_MAX)
        {
            step[i-1] = step[i]+1;
            enQueue(i-1);
        }
        if (i+1 < arrSize && step[i+1] == INIT_MAX)
        {
            step[i+1] = step[i]+1;
            enQueue(i+1);
        }

        if (visit[i] == 0)
        {
            for (int j = 0; j < arrSize; j++)
            {
                if (arr[j] == arr[i] && step[j] == INIT_MAX)
                {
                    step[j] = step[i] + 1;
                    enQueue(j);
                    visit[j] = 1;
                }
            }
        }
    }

    return step[0];
}

// @lc code=end



int minJumps(int* arr, int arrSize){
    InitQueue(arrSize);
    enQueue(0);
    int step = 0;
    int *visit = (int *)malloc(sizeof(int)*arrSize);
    memset(visit,0,sizeof(int)*arrSize);
    visit[0] = 1;

    while (!Empty()) // BFS会超时，用例通过8成
    {
        int cnt = QueueCnt();

        for (int i = 0; i < cnt; i++) // 错误：不知道在哪里增加step，最后发现没有按照轮数cnt来
        {
            int tmp = deQueue();
            if (tmp == arrSize-1)
            {
                return step;
            }
            
            if (tmp-1>=0 && tmp-1<arrSize && visit[tmp-1]==0)
            {
                visit[tmp-1] = 1;
                enQueue(tmp-1);
            }

            if (tmp+1 >= 0 && tmp+1<arrSize && visit[tmp+1]==0)
            {
                visit[tmp+1] = 1;
                enQueue(tmp+1);
            }

            for (int i = 0; i < arrSize; i++)
            {
                if (arr[i] == arr[tmp] && i != tmp && visit[i] == 0)
                {
                    visit[i] = 1;
                    enQueue(i);
                }
            }
        }
        step++;
    }
    DestoryQueue();
    return step;
}


// 解答错误，不满足无后效性，无法使用dp解答 通过21/31
#define INIT_MAX 0x0fffffff
#define MIN(a,b) ((a)>(b)?(b):(a))

void flush(int *arr, int arrSize, int i, int *step)
{
    // 同步刷新所有的步长
    for (int j = 0; j < i; j++)
    {
        step[j] = MIN(step[j], step[i]+i-j);
    }
    for (int j = i+1; j < arrSize; j++)
    {
        step[j] = MIN(step[j], step[i]+j-i);
    } 
    return;
}

void setsame(int *arr, int arrSize, int index, int *step)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == arr[index])
        {
            step[i] = MIN(step[i], step[index] + 1);

            // 同步刷新所有的步长
            flush(arr,arrSize,i,step);
        }
    }
    return;
}

int minJumps(int* arr, int arrSize){
    int *step = (int *)malloc(sizeof(int)*arrSize);
    for (int i = 0; i < arrSize; i++)
    {
        step[i] = INIT_MAX;
    }
    
    step[arrSize-1] = 0;
    for (int i = arrSize-1; i >= 0; i--)
    {
        if (i-1 >= 0)
        {
            step[i-1] = MIN(step[i]+1,step[i-1]);
            flush(arr,arrSize,i-1,step);
        }
        if (i+1 < arrSize)
        {
            step[i+1] = MIN(step[i]+1,step[i+1]);
            flush(arr,arrSize,i+1,step);
        }
        setsame(arr,arrSize,i,step);
    }

    return step[0];
}