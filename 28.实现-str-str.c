/*
 * @lc app=leetcode.cn id=28 lang=c
 *
 * [28] 实现 strStr()
 *
 * https://leetcode-cn.com/problems/implement-strstr/description/
 *
 * algorithms
 * Easy (39.38%)
 * Likes:    350
 * Dislikes: 0
 * Total Accepted:    120.6K
 * Total Submissions: 306.2K
 * Testcase Example:  '"hello"\n"ll"'
 *
 * 实现 strStr() 函数。
 * 
 * 给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置
 * (从0开始)。如果不存在，则返回  -1。
 * 
 * 示例 1:
 * 
 * 输入: haystack = "hello", needle = "ll"
 * 输出: 2
 * 
 * 
 * 示例 2:
 * 
 * 输入: haystack = "aaaaa", needle = "bba"
 * 输出: -1
 * 
 * 
 * 说明:
 * 
 * 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
 * 
 * 对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start
// 最好的实现方式，通过while 1实现单循环，指针通过回滚的方式恢复
int strStr(char * haystack, char * needle){
    int i=0;
    int j=0;

    if (*needle=='\0')
    {
        return 0;
    }    
    while (1)
    {
        if (needle[j]=='\0' || haystack[i]=='\0')
        {
            break;
        }

        if (needle[j]==haystack[i])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }

    if (needle[j]=='\0')
    {
        return i-j;
    }
    else
    {
        return -1;
    }
}
// 暴力破解的方法，时间和性能表现不太好；
int strStr0(char * haystack, char * needle){
    int i=0;

    if (*needle=='\0')
    {
        return 0;
    }    
    while (*(haystack+i)!='\0')
    {
        char *tmphay=haystack+i;
        char *tmpneedle=needle;
        while (*tmphay == *tmpneedle && *tmpneedle!='\0')
        {
            tmphay++;
            tmpneedle++;
        }
        if (*tmpneedle=='\0')
        {
            return i;
        }
        i++;
    }
    
    return -1;
}


// @lc code=end

int main(void)
{
    int result = 0;
    char str1[100];
    char str2[100];
    scanf("%s",&str1);
    scanf("%s",&str2);
    
    result = strStr(str1,str2);
    printf("%d\n",result);
    return 0;
}