/*
 * @lc app=leetcode.cn id=1016 lang=c
 *
 * [1016] 子串能表示从 1 到 N 数字的二进制串
 *
 * https://leetcode-cn.com/problems/binary-string-with-substrings-representing-1-to-n/description/
 *
 * algorithms
 * Medium (58.19%)
 * Likes:    27
 * Dislikes: 0
 * Total Accepted:    4.9K
 * Total Submissions: 8.4K
 * Testcase Example:  '"0110"\n3'
 *
 * 给定一个二进制字符串 S（一个仅由若干 '0' 和 '1' 构成的字符串）和一个正整数 N，如果对于从 1 到 N 的每个整数 X，其二进制表示都是 S
 * 的子串，就返回 true，否则返回 false。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：S = "0110", N = 3
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 输入：S = "0110", N = 4
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= S.length <= 1000
 * 1 <= N <= 10^9
 * 
 * 
 */

// @lc code=start
void Int2Str(char *str, int num)
{
    int i = 0;
    while (num != 0)
    {
        str[i++] = num%2 + '0';
        num = num >> 1;
    }
    // 需要反转才是正常的str;第一次这个地方出错了，忘记了反转
    for (int k = 0; k < i/2; k++)
    {
        char tmp = str[k];
        str[k] = str[i-k-1];
        str[i-k-1] = tmp;
    }
    
    return;
}

bool queryString(char * s, int n){
    char str[32] = {0};
    // memset(str, 0 ,sizeof(str));
    for (int i = 1; i <= n; i++)
    {
        Int2Str(str, i);
        if (strstr(s,str) == NULL)
        {
            return false;
        }
    }
    return true;
}
// @lc code=end

