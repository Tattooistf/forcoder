/*
 * @lc app=leetcode.cn id=441 lang=c
 *
 * [441] 排列硬币
 *
 * https://leetcode-cn.com/problems/arranging-coins/description/
 *
 * algorithms
 * Easy (41.99%)
 * Likes:    119
 * Dislikes: 0
 * Total Accepted:    46.4K
 * Total Submissions: 109.1K
 * Testcase Example:  '5'
 *
 * 你总共有 n 枚硬币，你需要将它们摆成一个阶梯形状，第 k 行就必须正好有 k 枚硬币。
 * 
 * 给定一个数字 n，找出可形成完整阶梯行的总行数。
 * 
 * n 是一个非负整数，并且在32位有符号整型的范围内。
 * 
 * 示例 1:
 * 
 * 
 * n = 5
 * 
 * 硬币可排列成以下几行:
 * ¤
 * ¤ ¤
 * ¤ ¤
 * 
 * 因为第三行不完整，所以返回2.
 * 
 * 
 * 示例 2:
 * 
 * 
 * n = 8
 * 
 * 硬币可排列成以下几行:
 * ¤
 * ¤ ¤
 * ¤ ¤ ¤
 * ¤ ¤
 * 
 * 因为第四行不完整，所以返回3.
 * 
 * 
 */

// @lc code=start

// 第一反应是使用暴力解题，没有想到可以使用二分法解题，所以特意做一下练练手
int arrangeCoins(int n){
    int left = 1;
    int right = n;

    while (left <= right) // 假定能有mid个完整台阶，计算sum是否小于n
    {
        long mid = left+(right-left)/2; // 居然漏了mid也可能超过int
        long sum = mid*(mid+1)/2;
        if (sum == n)
        {
            return mid;
        }
        else if (sum < n)
        {
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }
    return left-1;
}
// @lc code=end

