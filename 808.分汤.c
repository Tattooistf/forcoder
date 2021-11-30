/*
 * @lc app=leetcode.cn id=808 lang=c
 *
 * [808] 分汤
 *
 * https://leetcode-cn.com/problems/soup-servings/description/
 *
 * algorithms
 * Medium (46.78%)
 * Likes:    62
 * Dislikes: 0
 * Total Accepted:    4.1K
 * Total Submissions: 8.6K
 * Testcase Example:  '50'
 *
 * 有 A 和 B 两种类型的汤。一开始每种类型的汤有 N 毫升。有四种分配操作：
 * 
 * 
 * 提供 100ml 的汤A 和 0ml 的汤B。
 * 提供 75ml 的汤A 和 25ml 的汤B。
 * 提供 50ml 的汤A 和 50ml 的汤B。
 * 提供 25ml 的汤A 和 75ml 的汤B。
 * 
 * 
 * 
 * 当我们把汤分配给某人之后，汤就没有了。每个回合，我们将从四种概率同为0.25的操作中进行分配选择。如果汤的剩余量不足以完成某次操作，我们将尽可能分配。当两种类型的汤都分配完时，停止操作。
 * 
 * 注意不存在先分配100 ml汤B的操作。
 * 
 * 需要返回的值： 汤A先分配完的概率 + 汤A和汤B同时分配完的概率 / 2。
 * 
 * 
 * 示例:
 * 输入: N = 50
 * 输出: 0.625
 * 解释:
 * 如果我们选择前两个操作，A将首先变为空。对于第三个操作，A和B会同时变为空。对于第四个操作，B将首先变为空。
 * 所以A变为空的总概率加上A和B同时变为空的概率的一半是 0.25 *(1 + 1 + 0.5 + 0)= 0.625。
 * 
 * 
 * 注释: 
 * 
 * 
 * 0 <= N <= 10^9。
 * 
 * 返回值在 10^-6 的范围将被认为是正确的。
 * 
 * 
 * 
 */

// @lc code=start
// 不容易按照算法一个个套用，想到了使用DFS进行遍历的思路；但不确定正确性；没有考虑到dp的方式
// 还有种方式是递归法
// 最好的方法是dp，或者递归法+查表
double doResult(int A, int B);
// 递归容易出现超时,必须使用查表法优化时间
double mem[500][500] = {0.0};
double soupServings(int n){
    if (n > 10000)
    {   
        return 1.0;
    }
    int N = n/25 + (n%25 ? 1 : 0);
    mem[0][0] = 0.5;
    for (int i = 0; i <= N; i++)
    {
        mem[0][i] = 1;
        mem[i][0] = 0;
    }
    
    for (int i = 0; i <= N; i++)  // 坑，边界应该是<=N，少了一个，因为最后返回的是mem[N][N]
    {
        for (int j = 0; j <= N; j++)
        {
            mem[i][j] = doResult(i,j);
        }
    }
    
    return mem[N][N];
}
#define max(a) ((a)>0?(a):0)
double doResult(int A, int B)
{
    double ret = 0;
    if (A <= 0 && B <= 0)
    {
        ret = 0.5;
    }
    else if (A <= 0)
    {
        ret = 1;
    }
    else if (B <= 0)
    {
        ret = 0;
    }
    else
    {
        if (mem[A][B] != 0.0)
        {
            return mem[A][B];
        }
        mem[A][B] = 0.25 * (mem[max(A-4)][max(B)]+mem[max(A-3)][max(B-1)]+mem[max(A-2)][max(B-2)]+mem[max(A-1)][max(B-3)]);
        ret = mem[A][B];
    }

    return ret;
}
// @lc code=end

double doResult(int A, int B);
// 递归容易出现超时,必须使用查表法优化时间
double mem[500][500] = {0.0};
double soupServings(int n){
    if (n > 10000)
    {   
        return 1.0;
    }
    int N = n/25 + (n%25 ? 1 : 0);
    double ret = doResult(N,N);
    return ret;
}

double doResult(int A, int B)
{
    double ret = 0;
    if (A <= 0 && B <= 0)
    {
        ret = 0.5;
    }
    else if (A <= 0)
    {
        ret = 1;
    }
    else if (B <= 0)
    {
        ret = 0;
    }
    else
    {
        if (mem[A][B] != 0)
        {
            return mem[A][B];
        }
        ret = 0.25 * (doResult(A-4,B)+doResult(A-3,B-1)+doResult(A-2,B-2)+doResult(A-1,B-3));
        mem[A][B] = ret;
    }

    return ret;
}