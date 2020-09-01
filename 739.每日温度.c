/*
 * @lc app=leetcode.cn id=739 lang=c
 *
 * [739] 每日温度
 *
 * https://leetcode-cn.com/problems/daily-temperatures/description/
 *
 * algorithms
 * Medium (64.45%)
 * Likes:    480
 * Dislikes: 0
 * Total Accepted:    97.9K
 * Total Submissions: 151.9K
 * Testcase Example:  '[73,74,75,71,69,72,76,73]'
 *
 * 请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0
 * 来代替。
 * 
 * 例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4,
 * 2, 1, 1, 0, 0]。
 * 
 * 提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。
 * 
 */

// @lc code=start
int *g_Stack = NULL;
int g_Size = 0;
void InitStack(int size)
{
    g_Stack = (int *)malloc(sizeof(int)*size);
    memset(g_Stack,0,sizeof(int)*size);
    g_Size = 0;
    return;
}
void DestroyStack(void)
{
    if (g_Stack)
    {
        free(g_Stack);
    }
    g_Stack = NULL;
    g_Size = 0;
    return;
}
int StackEmpty(void)
{
    return (g_Size == 0);
}

void StackPush(int val)
{
    g_Stack[g_Size++] = val;
    return;
}

int StackPop(void)
{
    return g_Stack[--g_Size];
}

int StackTop(void)
{
    return g_Stack[g_Size-1];
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize){
    int *res = (int*)malloc(sizeof(int)*TSize);
    memset(res,0,sizeof(int)*TSize);
    *returnSize = TSize;

    InitStack(TSize);

    res[TSize-1] = 0;
    StackPush(TSize-1);

    for (int i = TSize-2; i >= 0; i--)
    {
        while (!StackEmpty() && T[i]>=T[StackTop()]) // 栽了一次坑，对于等于的情况忘记考虑
        {
            (void)StackPop();
        }

        if (StackEmpty())
        {
            res[i] = 0;
        }
        else
        {
            res[i] = StackTop() - i;
        }        
        StackPush(i);
    }

    DestroyStack();
    return res;    
}


// @lc code=end

