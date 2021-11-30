/*
 * @lc app=leetcode.cn id=354 lang=c
 *
 * [354] 俄罗斯套娃信封问题
 *
 * https://leetcode-cn.com/problems/russian-doll-envelopes/description/
 *
 * algorithms
 * Hard (42.92%)
 * Likes:    580
 * Dislikes: 0
 * Total Accepted:    68.5K
 * Total Submissions: 151.5K
 * Testcase Example:  '[[5,4],[6,4],[6,7],[2,3]]'
 *
 * 给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
 * 
 * 当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
 * 
 * 请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
 * 
 * 注意：不允许旋转信封。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
 * 输出：3
 * 解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
 * 
 * 示例 2：
 * 
 * 
 * 输入：envelopes = [[1,1],[1,1],[1,1]]
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * envelopes[i].length == 2
 * 1 i, hi 
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
        if (tmpa[0] > tmpb[0])
        {
            return 1;
        }

        if (tmpa[1] < tmpb[1]) // 必须降序，后续的值被选中，只选择最大的值
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}
// 没有思路；题解，先排序，然后按照最长递增序列进行动态规划求解
#define MAX(a,b) ((a)>(b)?(a):(b))
int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize){
    qsort(envelopes,envelopesSize,sizeof(int*),cmpmax);

    int *dp = (int *)malloc(sizeof(int)*envelopesSize);
    for (int i = 0; i < envelopesSize; i++)
    {
        dp[i] = 1;
    }
    
    int ret = 0;
    for (int i = 0; i < envelopesSize; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (envelopes[j][1] < envelopes[i][1])
            {
                dp[i] = MAX(dp[i], dp[j]+1);
            }
        }
        ret = MAX(dp[i],ret); // 错误：遗漏了关键的语句，没有选择整个数组最多的值
    }
    free(dp);

    return ret;
}
// @lc code=end

