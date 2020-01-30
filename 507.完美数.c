/*
 * @lc app=leetcode.cn id=507 lang=c
 *
 * [507] 完美数
 *
 * https://leetcode-cn.com/problems/perfect-number/description/
 *
 * algorithms
 * Easy (37.23%)
 * Likes:    45
 * Dislikes: 0
 * Total Accepted:    10.4K
 * Total Submissions: 27.8K
 * Testcase Example:  '28'
 *
 * 对于一个 正整数，如果它和除了它自身以外的所有正因子之和相等，我们称它为“完美数”。
 * 
 * 给定一个 整数 n， 如果他是完美数，返回 True，否则返回 False
 * 
 * 
 * 
 * 示例：
 * 
 * 输入: 28
 * 输出: True
 * 解释: 28 = 1 + 2 + 4 + 7 + 14
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 输入的数字 n 不会超过 100,000,000. (1e8)
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
// @lc code=start

// 第一次暴力破解，直接容易超时，但是反复提交几次也能通过
// 第一次优化：循环判断条件从num变成num/2
// 第二次优化：sum每次增加同时加上i和num/i；
// 第三次优化：增加i>=num/i时直接退出；前面通过sum加上num/i已经计算过；
bool checkPerfectNumber(int num){
    int sum=1;

    if (num<=1)/* 先去掉0和1两种特殊的情况 */
    {
        return false;
    }

    for (int i = 2; i <= num/2; i++)/* 这里可以将num/2修改成num/i，判断条件从<=变为< ;避免难以理解，此处不修改*/
    {
        if (i>=num/i)
        {
            break;
        }

        if (num%i==0)
        {
            sum+=i;
            sum+=num/i;
        }
    }

    if (sum==num)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// @lc code=end

int main(void)
{
    int res=0;
    int number=0;
    scanf("%d",&number);
    res = checkPerfectNumber(number);
    printf("%d\n",res);
    return 0;
}