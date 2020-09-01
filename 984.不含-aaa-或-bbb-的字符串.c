/*
 * @lc app=leetcode.cn id=984 lang=c
 *
 * [984] 不含 AAA 或 BBB 的字符串
 *
 * https://leetcode-cn.com/problems/string-without-aaa-or-bbb/description/
 *
 * algorithms
 * Medium (38.96%)
 * Likes:    50
 * Dislikes: 0
 * Total Accepted:    5.4K
 * Total Submissions: 14K
 * Testcase Example:  '1\n2'
 *
 * 给定两个整数 A 和 B，返回任意字符串 S，要求满足：
 * 
 * 
 * S 的长度为 A + B，且正好包含 A 个 'a' 字母与 B 个 'b' 字母；
 * 子串 'aaa' 没有出现在 S 中；
 * 子串 'bbb' 没有出现在 S 中。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：A = 1, B = 2
 * 输出："abb"
 * 解释："abb", "bab" 和 "bba" 都是正确答案。
 * 
 * 
 * 示例 2：
 * 
 * 输入：A = 4, B = 1
 * 输出："aabaa"
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= A <= 100
 * 0 <= B <= 100
 * 对于给定的 A 和 B，保证存在满足要求的 S。
 * 
 * 
 */

// @lc code=start


char * strWithout3a3b(int A, int B){
    int cnta = 0;
    int cntb = 0;
    int len = A+B;
    char *str = (char*)malloc(sizeof(char)*(len+1));
    memset(str,0,sizeof(char)*(len+1));
    char *res = str;

    while (strlen(res) < len) // 2、错误使用str，导致越界；应该使用res；
    {
        if ((A <= B && cntb == 2) || (A>B && cnta<2))
        {
            *str = 'a';
            str++;
            cnta++;
            cntb = 0;
            A--; // 1、忘记减去AB的个数
        }
        else
        {
            *str = 'b';
            str++;
            cnta = 0;
            cntb++;
            B--;
        }    
    }
    *str = '\0';
    return res;
}


// @lc code=end

