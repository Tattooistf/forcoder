/*
 * @lc app=leetcode.cn id=207 lang=c
 *
 * [207] 课程表
 *
 * https://leetcode-cn.com/problems/course-schedule/description/
 *
 * algorithms
 * Medium (50.23%)
 * Likes:    338
 * Dislikes: 0
 * Total Accepted:    38.5K
 * Total Submissions: 75.2K
 * Testcase Example:  '2\n[[1,0]]'
 *
 * 你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。
 * 
 * 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]
 * 
 * 给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？
 * 
 * 
 * 
 * 示例 1:
 * 
 * 输入: 2, [[1,0]] 
 * 输出: true
 * 解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
 * 
 * 示例 2:
 * 
 * 输入: 2, [[1,0],[0,1]]
 * 输出: false
 * 解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。详情请参见图的表示法。
 * 你可以假定输入的先决条件中没有重复的边。
 * 1 <= numCourses <= 10^5
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
// @lc code=start
bool dfs(int num,int** array,int size,int *visit)
{
    if (visit[num] == 1) // 提前判断能优化时间
    {
        return true;
    }
    if (visit[num] == -1) // 优化时栽坑，== 写成了 =，导致浪费时间，一直没搞明白问题在哪
    {
        return false;
    }    
    visit[num] = -1; // 表示当前正在访问
    for (int i = 0; i < size; i++)
    {
        if (num != array[i][0])
        {
            continue;
        }

        if (visit[array[i][1]] == -1)
        {
            return false;
        }

        if (!dfs(array[i][1],array,size,visit))
        {
            return false;
        }        
    }
    visit[num] = 1; // 表示已经访问过
    
    return true;
}

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    int *visit = (int *)malloc(sizeof(int)*numCourses);
    memset(visit,0,sizeof(int)*numCourses);
    for (int i = 0; i < numCourses; i++)
    {
        if (visit[i] != 0)
        {
            continue;
        }
        
        if (!dfs(i,prerequisites,prerequisitesSize,visit))
        {
            free(visit);
            return false;
        }
    }
    free(visit);
    return true;
}


// @lc code=end

