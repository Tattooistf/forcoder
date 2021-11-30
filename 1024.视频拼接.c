/*
 * @lc app=leetcode.cn id=1024 lang=c
 *
 * [1024] 视频拼接
 *
 * https://leetcode-cn.com/problems/video-stitching/description/
 *
 * algorithms
 * Medium (56.86%)
 * Likes:    237
 * Dislikes: 0
 * Total Accepted:    31.8K
 * Total Submissions: 56.6K
 * Testcase Example:  '[[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]]\n10'
 *
 * 你将会获得一系列视频片段，这些片段来自于一项持续时长为 T 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。
 * 
 * 视频片段 clips[i] 都用区间进行表示：开始于 clips[i][0] 并于 clips[i][1]
 * 结束。我们甚至可以对这些片段自由地再剪辑，例如片段 [0, 7] 可以剪切成 [0, 1] + [1, 3] + [3, 7] 三部分。
 * 
 * 我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, T]）。返回所需片段的最小数目，如果无法完成该任务，则返回 -1
 * 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
 * 输出：3
 * 解释：
 * 我们选中 [0,2], [8,10], [1,9] 这三个片段。
 * 然后，按下面的方案重制比赛片段：
 * 将 [1,9] 再剪辑为 [1,2] + [2,8] + [8,9] 。
 * 现在我们手上有 [0,2] + [2,8] + [8,10]，而这些涵盖了整场比赛 [0, 10]。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：clips = [[0,1],[1,2]], T = 5
 * 输出：-1
 * 解释：
 * 我们无法只用 [0,1] 和 [1,2] 覆盖 [0,5] 的整个过程。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：clips =
 * [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]],
 * T = 9
 * 输出：3
 * 解释： 
 * 我们选取片段 [0,4], [4,7] 和 [6,9] 。
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：clips = [[0,4],[2,8]], T = 5
 * 输出：2
 * 解释：
 * 注意，你可能录制超过比赛结束时间的视频。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * 0 
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
            return tmpa[1]<tmpb[1];
        }
        return 1;
    }
}

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

// 跳跃法思路与贪心法基本上一样，只是提前将maxend求解出来
int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time){
    int end = 0;
    int pre = 0;
    int ret = 0;
    int *maxend = (int *)malloc(sizeof(int)*time); // 错误：不能申请size大小，应该至少是time
    memset(maxend,0,sizeof(int)*time);
    for (int i = 0; i < clipsSize; i++)
    {
        if (clips[i][0] < time) // 错误：不能等于time，否则下标越界
        {
            maxend[clips[i][0]] = max(clips[i][1],maxend[clips[i][0]]);
        }
    }

    for (int i = 0; i < time; i++)
    {
        end = max(end,maxend[i]);
        if (end == i)
        {
            return -1;
        }
        
        if (i == pre)
        {
            ret++;
            pre = end;
        }
    }
    return ret;
}
// @lc code=end

// 贪心算法：每次找到最远的end
int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time){
    qsort(clips,clipsSize,sizeof(int*),cmpmax);
    
    int end = 0;
    int next = 0;
    int ret = 0;
    for (int i = 0; i < clipsSize && clips[i][0] <= end; )
    {
        while (i<clipsSize && clips[i][0] <= end)
        {
            next = max(next,clips[i][1]); // 错误：比较误使用end，实际上应该使用next比较
            i++;
        }
        ret++;
        end = next;
        if (end >= time)
        {
            return ret;
        }
    }
    
    return -1;
}

// 动态规划
int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time){
    int *dp = (int *)malloc(sizeof(int)*(time+1));
    memset(dp,0x5a,sizeof(int)*(time+1)); // 错误：应该是time+1，少了1，调试了很久

    dp[0] = 0;
    for (int t = 1; t <= time; t++)
    {
        for (int i = 0; i < clipsSize; i++)
        {
            if (clips[i][0] < t && t <= clips[i][1])
            {
                dp[t] = min(dp[t],dp[clips[i][0]]+1);
            }
        }
    }
    
    return (dp[time] == 0x5a5a5a5a) ? -1 : dp[time];
}
