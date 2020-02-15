/*
 * @lc app=leetcode.cn id=3 lang=c
 *
 * [3] 无重复字符的最长子串
 *
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (32.62%)
 * Likes:    3167
 * Dislikes: 0
 * Total Accepted:    347K
 * Total Submissions: 1.1M
 * Testcase Example:  '"abcabcbb"'
 *
 * 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 * 
 * 示例 1:
 * 
 * 输入: "abcabcbb"
 * 输出: 3 
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 * 
 * 
 * 示例 2:
 * 
 * 输入: "bbbbb"
 * 输出: 1
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
 * 
 * 
 * 示例 3:
 * 
 * 输入: "pwwkew"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 * 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include "math.h"
// @lc code=start
// 推荐的最佳解法，比较好理解；碰到第一个重复的字符的时候将起始字符删除，在原先基础上继续遍历；所以只需要一次遍历
// 调试花了点时间，end的增加只有在字符第一次出现时增加；错误的方式是每次遍历都增加，错误的用例“aaaaa”

int lengthOfLongestSubstring(char * s){
    int len=strlen(s);
    int max=0;
    int end=0,start=0;
    int array[128]={0};

    while(end<len)
    {
        if (array[s[end]]<1)
        {
            array[s[end++]]++;
            max=max>(end-start)?max:(end-start);
        }
        else
        {
            array[s[start]]--;
            start++;
        }
    }
    return max;
}



// @lc code=end
int main(void)
{
    char str[100]={0};
    scanf("%s",str);
    int len=lengthOfLongestSubstring(str);
    printf("%d\n",len);
    return 0;
}

// 思路完全正确，调试两次解决
// 第一次对非字母的字符没有考虑，直接数组访问异常
// 第二次对j的范围未做判断，也是访问越界
int lengthOfLongestSubstring2(char * s){
    int len=strlen(s);
    int max=0;
    int i=0;
    //int array[128]={0};

    for (i = 0; i < len-max; i++)
    {
        int j=0;
        // memset(array,0,sizeof(array));// 优化直接通过下面的局部变量定义，减少memset操作
        int array[128]={0};
        while (i+j<len && array[s[i+j]]<1)
        {
            array[s[i+j]]++;
            j++;
        }
        max=max>j?max:j;
    }
    return max;
}
