/*
 * @lc app=leetcode.cn id=436 lang=c
 *
 * [436] 寻找右区间
 *
 * https://leetcode-cn.com/problems/find-right-interval/description/
 *
 * algorithms
 * Medium (48.12%)
 * Likes:    83
 * Dislikes: 0
 * Total Accepted:    8.5K
 * Total Submissions: 17.4K
 * Testcase Example:  '[[1,2]]'
 *
 * 给你一个区间数组 intervals ，其中 intervals[i] = [starti, endi] ，且每个 starti 都 不同 。
 * 
 * 区间 i 的 右侧区间 可以记作区间 j ，并满足 startj >= endi ，且 startj 最小化 。
 * 
 * 返回一个由每个区间 i 的 右侧区间 的最小起始位置组成的数组。如果某个区间 i 不存在对应的 右侧区间 ，则下标 i 处的值设为 -1 。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：intervals = [[1,2]]
 * 输出：[-1]
 * 解释：集合中只有一个区间，所以输出-1。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：intervals = [[3,4],[2,3],[1,2]]
 * 输出：[-1, 0, 1]
 * 解释：对于 [3,4] ，没有满足条件的“右侧”区间。
 * 对于 [2,3] ，区间[3,4]具有最小的“右”起点;
 * 对于 [1,2] ，区间[2,3]具有最小的“右”起点。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：intervals = [[1,4],[2,3],[3,4]]
 * 输出：[-1, 2, -1]
 * 解释：对于区间 [1,4] 和 [3,4] ，没有满足条件的“右侧”区间。
 * 对于 [2,3] ，区间 [3,4] 有最小的“右”起点。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * intervals[i].length == 2
 * -10^6 i i 
 * 每个间隔的起点都 不相同
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
    else if (tmpa[0] == tmpb[0]) // 按照题目的描述，应该没有相等的情况
    {
        if (tmpa[1] < tmpb[1])
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

int binserach(int **arr,int size,int val,int start,int end)
{
    int left = start;
    int right = end;

    while (left < right)
    {
        int mid = left+(right-left)/2;
        if (arr[mid][0] < val)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
    }
    
    return left;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 思路正确：先按照start排序，存储索引，然后再二分法查找右区间
// 还有个双堆的方式，后面有时间了可以试试；效率应该比当前的实现好；
int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize){
    int **arr = (int **)malloc(sizeof(int*)*intervalsSize);
    for (int i = 0; i < intervalsSize; i++)
    {
        arr[i] = (int *)malloc(sizeof(int)*(intervalsColSize[0]+1));
        arr[i][0] = intervals[i][0];
        arr[i][1] = intervals[i][1];
        arr[i][2] = i;
    }
    qsort(arr, intervalsSize, sizeof(int*), cmpmax); // 错误：误使用了sizeof(int)*3，实际应该是指针大小

    int *ret = (int *)malloc(sizeof(int)*intervalsSize);
    for (int i = 0; i < intervalsSize; i++)
    {
        int tmp = binserach(arr,intervalsSize,arr[i][1],i,intervalsSize); // 错误：少考虑本身就是右区间的情况，查找应该从自身i开始
        if (tmp == intervalsSize)
        {
            ret[arr[i][2]] = -1;
        }
        else
        {
            ret[arr[i][2]] = arr[tmp][2]; // 错误：直接使用了tmp,应该是arr[tmp][2]才是索引
        }
    }
    *returnSize = intervalsSize;

    for (int i = 0; i < intervalsSize; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return ret;
}
// @lc code=end

