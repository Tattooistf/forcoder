/*
 * @lc app=leetcode.cn id=402 lang=c
 *
 * [402] 移掉K位数字
 *
 * https://leetcode-cn.com/problems/remove-k-digits/description/
 *
 * algorithms
 * Medium (29.04%)
 * Likes:    237
 * Dislikes: 0
 * Total Accepted:    19.2K
 * Total Submissions: 66.1K
 * Testcase Example:  '"1432219"\n3'
 *
 * 给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。
 * 
 * 注意:
 * 
 * 
 * num 的长度小于 10002 且 ≥ k。
 * num 不会包含任何前导零。
 * 
 * 
 * 示例 1 :
 * 
 * 
 * 输入: num = "1432219", k = 3
 * 输出: "1219"
 * 解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。
 * 
 * 
 * 示例 2 :
 * 
 * 
 * 输入: num = "10200", k = 1
 * 输出: "200"
 * 解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。
 * 
 * 
 * 示例 3 :
 * 
 * 
 * 输入: num = "10", k = 2
 * 输出: "0"
 * 解释: 从原数字移除所有的数字，剩余为空就是0。
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
// @lc code=start
#define MAX 10002
char g_stack[MAX]={0};
int g_top = 0;

void stackinit(void)
{
    memset(g_stack,0,sizeof(g_stack));
    g_top = 0;
    return;
}
void push(int a)
{
    g_stack[g_top] = a;
    g_top++;
    return;
}

int pop()
{
    return g_stack[--g_top];
}

char * removeKdigits(char * num, int k){
    stackinit(); // 全局变量踩过坑，初始化方式残留影响
    int len = strlen(num);
    int intk = k;
    if (k >= len)
    {
        return "0";
    }

    for (int i = 0; i < len; i++)
    {
        while (g_top > 0 && g_stack[g_top-1] > num[i] && intk > 0) //先后顺序关系很大
        {
            pop();
            intk--;
        }
        
        if (num[i] != '0' || g_top > 0)
        {
            push(num[i]);
        }
    }

    while (intk > 0 && g_top > 0)
    {
        pop();
        intk--;
    }
    
    if (g_top <= 0) // 最刚开始没有考虑为空的情况
    {
        return "0";
    }
    g_stack[g_top]='\0';// 没有考虑pop后残留的问题 
    #if 0 //第一次直接转换新内存空间，一次通过
    char *res = (char *)malloc(sizeof(char)*(g_top+1));
    res[g_top] = '\0';
    while (g_top > 0)
    {
        int tmp = pop();
        res[g_top] = tmp;
    }
    #endif
    return g_stack;
}


// @lc code=end
int main(void)
{
    char *result = NULL;
    char *str = "10200";
    result = removeKdigits(str,1);
    printf("%s\n",result);
    return 0;
}
