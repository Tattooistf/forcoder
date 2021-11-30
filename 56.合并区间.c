/*
 * @lc app=leetcode.cn id=56 lang=c
 *
 * [56] 合并区间
 *
 * https://leetcode-cn.com/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (44.55%)
 * Likes:    1031
 * Dislikes: 0
 * Total Accepted:    267K
 * Total Submissions: 576.9K
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi]
 * 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
 * 输出：[[1,6],[8,10],[15,18]]
 * 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：intervals = [[1,4],[4,5]]
 * 输出：[[1,5]]
 * 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * intervals[i].length == 2
 * 0 i i 
 * 
 * 
 */

// @lc code=start

int cmpmax(const void *a, const void *b)
{
    int *tmpa = *(int **)a;
    int *tmpb = *(int **)b;

    if (tmpa[0] < tmpb[0])
    {
        return -1;
    }
    else
    {
        if (tmpa[0] == tmpb[0])
        {
            return tmpa[1] < tmpb[1];
        }
        return 1;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    qsort(intervals, intervalsSize, sizeof(int*), cmpmax);
    int **ret = (int **)malloc(sizeof(int *)*intervalsSize);
    memset(ret, 0, sizeof(int*)*intervalsSize);
    *returnSize = 0;
    int *col = (int *)malloc(sizeof(int)*intervalsSize);
    memset(col,0,sizeof(int)*intervalsSize);
    for (int i = 0; i < intervalsSize; i++)
    {
        col[i] = 2;
    }

    int start = intervals[0][0];
    int end = intervals[0][1];
    for (int i = 1; i < intervalsSize; i++)
    {
        if (intervals[i][0] > end)
        {
            int *arr = (int *)malloc(sizeof(int)*2);
            arr[0] = start;
            arr[1] = end;
            ret[*returnSize] = arr;
            (*returnSize)++;
            start = intervals[i][0];
        }

        if (intervals[i][1] > end)
        {
            end = intervals[i][1];
        }
    }
    int *arr = (int *)malloc(sizeof(int)*2);
    arr[0] = start;
    arr[1] = end;
    ret[*returnSize] = arr;
    (*returnSize)++;
    *returnColumnSizes = col; // 又是这个地方栽了很久，没有理解行size是需要将数组传递出去；前面使用(*returnColumnSizes)[*returnsize]的方式异常调试半天

    return ret;
    
}
// @lc code=end

