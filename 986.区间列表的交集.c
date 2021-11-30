/*
 * @lc app=leetcode.cn id=986 lang=c
 *
 * [986] 区间列表的交集
 *
 * https://leetcode-cn.com/problems/interval-list-intersections/description/
 *
 * algorithms
 * Medium (66.58%)
 * Likes:    173
 * Dislikes: 0
 * Total Accepted:    19.2K
 * Total Submissions: 28.7K
 * Testcase Example:  '[[0,2],[5,10],[13,23],[24,25]]\n[[1,5],[8,12],[15,24],[25,26]]'
 *
 * 给定两个由一些 闭区间 组成的列表，firstList 和 secondList ，其中 firstList[i] = [starti, endi] 而
 * secondList[j] = [startj, endj] 。每个区间列表都是成对 不相交 的，并且 已经排序 。
 * 
 * 返回这 两个区间列表的交集 。
 * 
 * 形式上，闭区间 [a, b]（其中 a ）表示实数 x 的集合，而 a  。
 * 
 * 两个闭区间的 交集 是一组实数，要么为空集，要么为闭区间。例如，[1, 3] 和 [2, 4] 的交集为 [2, 3] 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：firstList = [[0,2],[5,10],[13,23],[24,25]], secondList =
 * [[1,5],[8,12],[15,24],[25,26]]
 * 输出：[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：firstList = [[1,3],[5,9]], secondList = []
 * 输出：[]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：firstList = [], secondList = [[4,8],[10,12]]
 * 输出：[]
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：firstList = [[1,7]], secondList = [[3,10]]
 * 输出：[[3,7]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 
 * firstList.length + secondList.length >= 1
 * 0 i < endi 
 * endi < starti+1
 * 0 j < endj 
 * endj < startj+1
 * 
 * 
 */

// @lc code=start

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** intervalIntersection(int** firstList, int firstListSize, int* firstListColSize, int** secondList, int secondListSize, int* secondListColSize, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    if (firstListSize == 0 || secondListSize == 0)
    {
        return NULL;
    }

    int size = firstListSize+secondListSize; // 第一个错误，size大小判断错误，之前以为是最小值就行
    int **ret = (int **)malloc(sizeof(int*)*size);
    memset(ret,0,sizeof(int*)*size);

    int *col = (int *)malloc(sizeof(int)*size);
    memset(col,0,sizeof(int)*size);
    // for (int i = 0; i < size; i++)
    // {
    //     col[i]=2;
    // }
    
    int i = 0;
    int j = 0;
    while (i < firstListSize && j < secondListSize)
    {
        if ((firstList[i][0] <= secondList[j][1]) && (firstList[i][1] >= secondList[j][0]))
        {
            // add(start,end);
            int *arr = (int *)malloc(sizeof(int)*2);
            arr[0] = max(secondList[j][0],firstList[i][0]);
            arr[1] = min(firstList[i][1],secondList[j][1]);
            ret[*returnSize] = arr;
            col[*returnSize] = 2;
            (*returnSize)++;            
        }
        // else // 第二个错误，以为else才需要走进去，实际上每次都必须走，不断比较后面的值
        {
            if (secondList[j][1] < firstList[i][1])
            {
                j++;
            }
            else
            {
                i++;
            }
        }
    }
    
    *returnColumnSizes = col;
    return ret;
}
// @lc code=end

