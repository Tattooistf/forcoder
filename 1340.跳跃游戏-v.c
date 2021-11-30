/*
 * @lc app=leetcode.cn id=1340 lang=c
 *
 * [1340] 跳跃游戏 V
 *
 * https://leetcode-cn.com/problems/jump-game-v/description/
 *
 * algorithms
 * Hard (55.36%)
 * Likes:    67
 * Dislikes: 0
 * Total Accepted:    4.2K
 * Total Submissions: 7.3K
 * Testcase Example:  '[6,4,14,6,8,13,9,7,10,6,12]\n2'
 *
 * 给你一个整数数组 arr 和一个整数 d 。每一步你可以从下标 i 跳到：
 * 
 * 
 * i + x ，其中 i + x < arr.length 且 0 < x <= d 。
 * i - x ，其中 i - x >= 0 且 0 < x <= d 。
 * 
 * 
 * 除此以外，你从下标 i 跳到下标 j 需要满足：arr[i] > arr[j] 且 arr[i] > arr[k] ，其中下标 k 是所有 i 到 j
 * 之间的数字（更正式的，min(i, j) < k < max(i, j)）。
 * 
 * 你可以选择数组的任意下标开始跳跃。请你返回你 最多 可以访问多少个下标。
 * 
 * 请注意，任何时刻你都不能跳到数组的外面。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
 * 输出：4
 * 解释：你可以从下标 10 出发，然后如上图依次经过 10 --> 8 --> 6 --> 7 。
 * 注意，如果你从下标 6 开始，你只能跳到下标 7 处。你不能跳到下标 5 处因为 13 > 9 。你也不能跳到下标 4 处，因为下标 5 在下标 4 和
 * 6 之间且 13 > 9 。
 * 类似的，你不能从下标 3 处跳到下标 2 或者下标 1 处。
 * 
 * 
 * 示例 2：
 * 
 * 输入：arr = [3,3,3,3,3], d = 3
 * 输出：1
 * 解释：你可以从任意下标处开始且你永远无法跳到任何其他坐标。
 * 
 * 
 * 示例 3：
 * 
 * 输入：arr = [7,6,5,4,3,2,1], d = 1
 * 输出：7
 * 解释：从下标 0 处开始，你可以按照数值从大到小，访问所有的下标。
 * 
 * 
 * 示例 4：
 * 
 * 输入：arr = [7,1,7,1,7,1], d = 2
 * 输出：2
 * 
 * 
 * 示例 5：
 * 
 * 输入：arr = [66], d = 1
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= arr.length <= 1000
 * 1 <= arr[i] <= 10^5
 * 1 <= d <= arr.length
 * 
 * 
 */

// @lc code=start

// 昨天晚上想30min没想到思路，以为是栈+某个算法。今天中午突然想到每次都是依赖他能跳到的最大值，有依赖关系可以dp或递归
int cmpmax(const void *a, const void *b)
{
    int *tmpa = *((int **)a);
    int *tmpb = *((int **)b);
    if (tmpa[1] < tmpb[1])
    {
        return -1;
    }

    if (tmpa[1] == tmpb[1])
    {
        if (tmpa[0] < tmpb[0])
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    return 1;
}
#define MAX(a,b) ((a)>(b)?(a):(b))

int maxJumps(int* arr, int arrSize, int d){
    int *dp = (int *)malloc(sizeof(int)*(arrSize));
    int **new = (int *)malloc(sizeof(int*)*arrSize);
    for (int i = 0; i < arrSize; i++)
    {
        int *p = malloc(sizeof(int)*2);
        p[0] = i;
        p[1] = arr[i];
        new[i] = p;
        dp[i] = 1;
    }
    qsort(new,arrSize,sizeof(int*),cmpmax);
    int max = 0;
    for (int i = 0; i < arrSize; i++)
    {
        int index = new[i][0];
        // 往大的方向遍历
        for (int j = index+1; j < arrSize && j <= index+d; j++)
        {
            if (arr[j] >= new[i][1]) // 错误：用了>，实际上应该是>=
            {
                break;
            }
            dp[index] = MAX(dp[index], dp[j]+1);
        }

        // 往小的方向遍历
        for (int j = index-1; j >= 0 && j >= index-d; j--)
        {
            if (arr[j] >= new[i][1])
            {
                break;
            }
            dp[index] = MAX(dp[index], dp[j]+1);
        }  
        max = MAX(max, dp[index]);      
    }
    free(dp);
    for (int i = 0; i < arrSize; i++)
    {
        if (new[i]!=NULL)
        {
            free(new[i]);
        }
    }
    free(new);
    return max;
}
// @lc code=end

