/*
 * @lc app=leetcode.cn id=754 lang=c
 *
 * [754] 到达终点数字
 *
 * https://leetcode-cn.com/problems/reach-a-number/description/
 *
 * algorithms
 * Medium (40.96%)
 * Likes:    128
 * Dislikes: 0
 * Total Accepted:    5.9K
 * Total Submissions: 14.3K
 * Testcase Example:  '1'
 *
 * 在一根无限长的数轴上，你站在0的位置。终点在target的位置。
 * 
 * 每次你可以选择向左或向右移动。第 n 次移动（从 1 开始），可以走 n 步。
 * 
 * 返回到达终点需要的最小移动次数。
 * 
 * 示例 1:
 * 
 * 
 * 输入: target = 3
 * 输出: 2
 * 解释:
 * 第一次移动，从 0 到 1 。
 * 第二次移动，从 1 到 3 。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: target = 2
 * 输出: 3
 * 解释:
 * 第一次移动，从 0 到 1 。
 * 第二次移动，从 1 到 -1 。
 * 第三次移动，从 -1 到 2 。
 * 
 * 
 * 注意:
 * 
 * 
 * target是在[-10^9, 10^9]范围中的非零整数。
 * 
 * 
 */

// @lc code=start

// MD，这道题和DFS没有半毛钱关系，看target后还花了好多时间在这条思路上
// 直接简单的数学推理解决；第一次想到了数据序列的+-符号组合，没想到好的退出条件
int reachNumber(int target){
    if (target < 0)
    {
        target = -target;
    }

    int sum = 0;
    int step = 1;
    while (1)
    {
        sum=(step*(step+1))>>1;
        if ((sum >= target) && (((sum - target)&0x1) == 0)) //栽坑：忘记增加括号，导致&0x1先与0进行判断
        {
            return step;
        }
        step++;                
    }
    return 0;
}


// @lc code=end
int main()
{
    int res = 0;
    res = reachNumber(1);
    return 0;
}
