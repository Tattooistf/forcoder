/*
 * @lc app=leetcode.cn id=798 lang=c
 *
 * [798] 得分最高的最小轮调
 *
 * https://leetcode-cn.com/problems/smallest-rotation-with-highest-score/description/
 *
 * algorithms
 * Hard (44.19%)
 * Likes:    59
 * Dislikes: 0
 * Total Accepted:    1K
 * Total Submissions: 2.3K
 * Testcase Example:  '[2,3,1,4,0]'
 *
 * 给定一个数组 A，我们可以将它按一个非负整数 K 进行轮调，这样可以使数组变为 A[K], A[K+1], A{K+2], ... A[A.length
 * - 1], A[0], A[1], ..., A[K-1] 的形式。此后，任何值小于或等于其索引的项都可以记作一分。
 * 
 * 例如，如果数组为 [2, 4, 1, 3, 0]，我们按 K = 2 进行轮调后，它将变成 [1, 3, 0, 2, 4]。这将记作 3 分，因为 1
 * > 0 [no points], 3 > 1 [no points], 0 <= 2 [one point], 2 <= 3 [one point],
 * 4 <= 4 [one point]。
 * 
 * 在所有可能的轮调中，返回我们所能得到的最高分数对应的轮调索引 K。如果有多个答案，返回满足条件的最小的索引 K。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：[2, 3, 1, 4, 0]
 * 输出：3
 * 解释：
 * 下面列出了每个 K 的得分：
 * K = 0,  A = [2,3,1,4,0],    score 2
 * K = 1,  A = [3,1,4,0,2],    score 3
 * K = 2,  A = [1,4,0,2,3],    score 3
 * K = 3,  A = [4,0,2,3,1],    score 4
 * K = 4,  A = [0,2,3,1,4],    score 3
 * 所以我们应当选择 K = 3，得分最高。
 * 
 * 示例 2：
 * 
 * 输入：[1, 3, 0, 2, 4]
 * 输出：0
 * 解释：
 * A 无论怎么变化总是有 3 分。
 * 所以我们将选择最小的 K，即 0。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * A 的长度最大为 20000。
 * A[i] 的取值范围是 [0, A.length]。
 * 
 * 
 */

// @lc code=start


int bestRotation(int* A, int ASize){
    int *diff = malloc(sizeof(int)*(ASize+1)); // 为什么需要+1:因为循环中有i+1，i表示步数，如果i等于最大则会溢出，所以申请ASize+1
    memset(diff,0,sizeof(int)*(ASize+1));

    for (int i = 0; i < ASize; i++)
    {
        if (A[i] <= i)  //为什么需要==:相等的时候不能走下面的分支
        {
            diff[0] += 1;
            diff[i - A[i]+1] -= 1;
            diff[i+1] += 1;
        }
        else
        {
            diff[i+1] += 1;
            diff[ASize - A[i]+i+1]-=1;
        }
    }
    int sum = 0;
    int max = 0;
    int pzs = 0;
    for (int i = 0; i < ASize; i++) //step
    {
        sum += diff[i];
        if (sum > max)
        {
            max = sum;
            pzs = i;
        }
    }
    free(diff);
    diff=NULL;
    return pzs;
}


// @lc code=end

