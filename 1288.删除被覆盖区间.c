/*
 * @lc app=leetcode.cn id=1288 lang=c
 *
 * [1288] 删除被覆盖区间
 *
 * https://leetcode-cn.com/problems/remove-covered-intervals/description/
 *
 * algorithms
 * Medium (55.69%)
 * Likes:    10
 * Dislikes: 0
 * Total Accepted:    2.6K
 * Total Submissions: 4.6K
 * Testcase Example:  '[[1,4],[3,6],[2,8]]'
 *
 * 给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。
 * 
 * 只有当 c <= a 且 b <= d 时，我们才认为区间 [a,b) 被区间 [c,d) 覆盖。
 * 
 * 在完成所有删除操作后，请你返回列表中剩余区间的数目。
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 输入：intervals = [[1,4],[3,6],[2,8]]
 * 输出：2
 * 解释：区间 [3,6] 被区间 [2,8] 覆盖，所以它被删除了。
 * 
 * 
 * 
 * 
 * 提示：​​​​​​
 * 
 * 
 * 1 <= intervals.length <= 1000
 * 0 <= intervals[i][0] < intervals[i][1] <= 10^5
 * 对于所有的 i != j：intervals[i] != intervals[j]
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
// @lc code=start
int cmp(const void *a,const void *b)
{
    int *tmpa = *(int **)a;
    int *tmpb = *(int **)b;
    if (tmpa[0] == tmpb[0])
    {
        return tmpa[1] < tmpb[1];
    }

    return tmpa[0] > tmpb[0];
}

int removeCoveredIntervals(int** intervals, int intervalsSize, int* intervalsColSize){
    qsort(intervals,intervalsSize,sizeof(int*),cmp);
    int count = 1;
    int max = intervals[0][1];
    for (int i = 0; i < intervalsSize; i++)
    {
        if (max < intervals[i][1])
        {
            count++;
            max = intervals[i][1];
        }
        
    }
    return count;
}
// @lc code=end
int g_A[2] = {1,4};
int g_B[2] = {3,6};
int g_C[2] = {2,8};
int *g_Array[3] = {g_A,g_B,g_C};

int g_Col[3] = {2,2,2};
int main(void)
{
    int result = 0;
    result = removeCoveredIntervals(g_Array,sizeof(g_Array)/sizeof(g_Array[0]),g_Col);
    return 0;
}

// 原始解法，考虑太多，常规思路计算覆盖个数，再减除；使用计算未覆盖更好
int removeCoveredIntervals0(int** intervals, int intervalsSize, int* intervalsColSize){
    qsort(intervals,intervalsSize,sizeof(int*),cmp);
    int count = intervalsSize;
    for (int i = 0; i < intervalsSize; i++)
    {
        if (intervals[i][0] == 0xffffffff)
        {
            continue;
        }
        
        for (int j = i+1; j < intervalsSize; j++)
        {                        
            if ((intervals[i][1] >= intervals[j][1]) && (intervals[j][0] != 0xffffffff))
            {
                count--;
                intervals[j][0] = 0xffffffff;
            }
        }
    }
    return count;
}