/*
 * @lc app=leetcode.cn id=435 lang=c
 *
 * [435] 无重叠区间
 *
 * https://leetcode-cn.com/problems/non-overlapping-intervals/description/
 *
 * algorithms
 * Medium (44.96%)
 * Likes:    125
 * Dislikes: 0
 * Total Accepted:    12K
 * Total Submissions: 26.7K
 * Testcase Example:  '[[1,2]]'
 *
 * 给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。
 * 
 * 注意:
 * 
 * 
 * 可以认为区间的终点总是大于它的起点。
 * 区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: [ [1,2], [2,3], [3,4], [1,3] ]
 * 
 * 输出: 1
 * 
 * 解释: 移除 [1,3] 后，剩下的区间没有重叠。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: [ [1,2], [1,2], [1,2] ]
 * 
 * 输出: 2
 * 
 * 解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。
 * 
 * 
 * 示例 3:
 * 
 * 
 * 输入: [ [1,2], [2,3] ]
 * 
 * 输出: 0
 * 
 * 解释: 你不需要移除任何区间，因为它们已经是无重叠的了。
 * 
 * 
 */

// @lc code=start
//思路基本正确：先排序，后面处理；处理环节花了很长时间才想明白需要记录最小终点值，利用它来判断下次是否需要+1
//想到最小终点值后编写完成1次提交通过，但排序性能不好。通过快排能提升性能，快排尚有疑问
int cmpmax(const void *a,const void *b)
{
    int *range1 = *(int **)a;
    int *range2 = *(int **)b;
    if (range1[1] == range2[1]) {
        return range2[0] - range1[0];
    }  else {
        return range1[1] - range2[1];
    } 
}
int eraseOverlapIntervals(int** intervals, int intervalsSize, int* intervalsColSize){
    int i=0;
    if (intervalsSize<2 || intervals==NULL)
    {
        return 0;
    }
    //qsort(intervals,intervalsSize,sizeof(intervals[0]),cmpmax);
    #if 1
    for (i = 0; i < intervalsSize; i++)
    {
        for (int j = i+1; j < intervalsSize; j++)
        {
            if (intervals[i][0]>intervals[j][0])
            {
                // 需要整体都进行交换
                int tmp=intervals[i][0];
                intervals[i][0]=intervals[j][0];
                intervals[j][0]=tmp;
                
                tmp=intervals[i][1];
                intervals[i][1]=intervals[j][1];
                intervals[j][1]=tmp;                
            }
        }
    }
    #endif

    int boudry=intervals[0][1];//存储已处理的数组终点的最小值
    int count=0;
    for (i = 1; i < intervalsSize; i++)
    {
        if (boudry>intervals[i][0]) //如果新节点起点小于最小值，则一定需要++
        {
            boudry=(boudry>=intervals[i][1])?intervals[i][1]:boudry; //如果新节点终点小于最小值，则刷新为最小值
            count++;
        }
        else //如果新节点起点大于等于最小值，则将新节点终点设置为最小值
        {
            boudry=intervals[i][1];
        }
    }
    return count;
}


// @lc code=end

