/*
 * @lc app=leetcode.cn id=1071 lang=c
 *
 * [1071] 字符串的最大公因子
 *
 * https://leetcode-cn.com/problems/greatest-common-divisor-of-strings/description/
 *
 * algorithms
 * Easy (58.60%)
 * Likes:    202
 * Dislikes: 0
 * Total Accepted:    33.6K
 * Total Submissions: 57.3K
 * Testcase Example:  '"ABCABC"\n"ABC"'
 *
 * 对于字符串 S 和 T，只有在 S = T + ... + T（T 自身连接 1 次或多次）时，我们才认定 “T 能除尽 S”。
 * 
 * 返回最长字符串 X，要求满足 X 能除尽 str1 且 X 能除尽 str2。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：str1 = "ABCABC", str2 = "ABC"
 * 输出："ABC"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：str1 = "ABABAB", str2 = "ABAB"
 * 输出："AB"
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：str1 = "LEET", str2 = "CODE"
 * 输出：""
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * str1[i] 和 str2[i] 为大写英文字母
 * 
 * 
 */

// @lc code=start

#define MAX(a,b) ((a)>(b)?(a):(b))
int valid(char *s, int len)
{
    if (strlen(s)%len != 0) // 前面漏了长度倍数的判断
    {
        return 0;
    }
    
    for (int i = 0; i < strlen(s); i++)
    {
        if(s[i] != s[i%len])
        {
            return 0;
        }
    }
    return 1;
}

char * gcdOfStrings(char * str1, char * str2){
    int i = 0;
    int max = 0;
    while (i < strlen(str1) && i < strlen(str2))
    {
        if (str1[i] != str2[i])
        {
            return "";
        }
        i++;
        if(!valid(str1,i)) continue;
        if(!valid(str2,i)) continue;
        max = MAX(max, i);
    }
    char *ret = NULL;
    ret = (char *)malloc(sizeof(char)*(max+1));
    memset(ret,0,sizeof(char)*(max+1)); // 没有初始化结束符\0，导致花了很长时间
    strncpy(ret, str1, max);
    
    return ret;
}
// @lc code=end

