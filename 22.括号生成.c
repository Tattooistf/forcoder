/*
 * @lc app=leetcode.cn id=22 lang=c
 *
 * [22] 括号生成
 *
 * https://leetcode-cn.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (72.95%)
 * Likes:    725
 * Dislikes: 0
 * Total Accepted:    70.6K
 * Total Submissions: 96.6K
 * Testcase Example:  '3'
 *
 * 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
 * 
 * 例如，给出 n = 3，生成结果为：
 * 
 * [
 * ⁠ "((()))",
 * ⁠ "(()())",
 * ⁠ "(())()",
 * ⁠ "()(())",
 * ⁠ "()()()"
 * ]
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


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 关键点括号有效的判断条件，右括号永远小于左括号数目；左括号小于一半数目
// 一个细节没注意好，没有一次过：returnSize没有初始化，直接后面做数组下标导致访问异常
void find(int deep,char **str,int *count,char *result,int len,int left,int right)
{
    if (deep==len)
    {
        result[deep]='\0';
        char *tmp=(char*)malloc(deep+1);
        strcpy(tmp,result);
        tmp[deep]='\0';
        str[(*count)++]=tmp;
        return;
    }

    if (left < (len>>1))
    {
        result[deep]='(';
        find(deep+1,str,count,result,len,left+1,right);
        result[deep]='\0';
    }
    if (left>right)
    {
        result[deep]=')';
        find(deep+1,str,count,result,len,left,right+1);    
        result[deep]='\0';            
    }
    
    return;
    
}

char ** generateParenthesis(int n, int* returnSize){
    *returnSize=0;
    if (n<1)
    {
        return NULL;
    }
    
    int size = pow(2,2*n);
    char **arrayptr=(char **)malloc(sizeof(char *)*size);
    char *strtmp=(char*)malloc(2*n+1);
    find(0,arrayptr,returnSize,strtmp,2*n,0,0);
    return arrayptr;

}


// @lc code=end

int main(void)
{
    char **ret=NULL;
    int count=0;
    ret=generateParenthesis(3,&count);
    while (count)
    {
        printf("%s\n",ret[count-1]);
        count--;
    }
    
    return 0;
}
