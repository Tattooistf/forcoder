/*
 * @lc app=leetcode.cn id=735 lang=c
 *
 * [735] 行星碰撞
 *
 * https://leetcode-cn.com/problems/asteroid-collision/description/
 *
 * algorithms
 * Medium (40.05%)
 * Likes:    177
 * Dislikes: 0
 * Total Accepted:    18.6K
 * Total Submissions: 45.8K
 * Testcase Example:  '[5,10,-5]'
 *
 * 给定一个整数数组 asteroids，表示在同一行的行星。
 * 
 * 对于数组中的每一个元素，其绝对值表示行星的大小，正负表示行星的移动方向（正表示向右移动，负表示向左移动）。每一颗行星以相同的速度移动。
 * 
 * 
 * 找出碰撞后剩下的所有行星。碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。两颗移动方向相同的行星，永远不会发生碰撞。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：asteroids = [5,10,-5]
 * 输出：[5,10]
 * 解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。
 * 
 * 示例 2：
 * 
 * 
 * 输入：asteroids = [8,-8]
 * 输出：[]
 * 解释：8 和 -8 碰撞后，两者都发生爆炸。
 * 
 * 示例 3：
 * 
 * 
 * 输入：asteroids = [10,2,-5]
 * 输出：[10]
 * 解释：2 和 -5 发生碰撞后剩下 -5 。10 和 -5 发生碰撞后剩下 10 。
 * 
 * 示例 4：
 * 
 * 
 * 输入：asteroids = [-2,-1,1,2]
 * 输出：[-2,-1,1,2]
 * 解释：-2 和 -1 向左移动，而 1 和 2 向右移动。 由于移动方向相同的行星不会发生碰撞，所以最终没有行星发生碰撞。 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 
 * -1000 
 * asteroids[i] != 0
 * 
 * 
 */

// @lc code=start

int Stack[10001] = {0};
int g_Top = 0;
int g_Size = 0;

void StackInit(void)
{
    memset(Stack,0,sizeof(Stack));
    g_Top = 0;
    g_Size = sizeof(Stack)/sizeof(Stack[0]);
    return;
}

void StackPush(int val)
{
    Stack[g_Top] = val;
    g_Top++;

    return;
}

int StackPop(void)
{
    return Stack[--g_Top];
}

int isEmpty(void)
{
    return (g_Top == 0);
}

int StackTop(void) 
{
    return Stack[g_Top-1];
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize){
    StackInit();
    int idx = 0;
    int *arr = (int *)malloc(sizeof(int)*asteroidsSize);
    for (int i = 0; i < asteroidsSize; i++)
    {
        if (asteroids[i] > 0)
        {
            StackPush(asteroids[i]);
            continue;
        }
        
        int tmp = -1;
        while (!isEmpty())
        {
            tmp = (StackTop() + asteroids[i]);
            if (tmp < 0)
            {
                StackPop();
            }
            else if (tmp == 0)
            {
                StackPop();
                break;
            }
            else
            {
                break;
            }
        }

        if (tmp >= 0) // 错误：等于和大于的情况都不需要存储，只有小于的情况需要存储
        {
            continue;
        }
        
        arr[idx++] = asteroids[i];
    }

    memcpy(arr+idx,Stack,sizeof(int)*g_Top);
    *returnSize = idx + g_Top;

    return arr;
}
// @lc code=end

