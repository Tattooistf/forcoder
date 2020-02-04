/*
 * @lc app=leetcode.cn id=17 lang=c
 *
 * [17] 电话号码的字母组合
 *
 * https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (52.11%)
 * Likes:    564
 * Dislikes: 0
 * Total Accepted:    73.4K
 * Total Submissions: 140.7K
 * Testcase Example:  '"23"'
 *
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 * 
 * 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 * 
 * 
 * 
 * 示例:
 * 
 * 输入："23"
 * 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * 
 * 
 * 说明:
 * 尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
// @lc code=start

// 题目还有问题，不知道什么原因，用例“2”调试能通过，提交就异常，待定位
char *data[10]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
char ch[100]={0};
int count=0;
void dfs(int deep,char* digits,char **retstr);
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char * digits, int* returnSize){
    // 全局变量一定要归零，巨大无比的坑
    count=0;
    *returnSize = 0;
    if (strlen(digits)<1)
    {
        return NULL;
    }
    
    char **ret=(char**)malloc(sizeof(char*)*1000);
    dfs(0,digits,ret);
    *returnSize = count;

    return ret;
}

void dfs(int deep,char* digits,char **retstr)
{
    int length=strlen(digits);
    if (deep == length)
    {
        char *str = (char *)malloc(length+1);
        ch[deep]='\0';
        strcpy(str,ch);
        str[deep]='\0';
        retstr[count++] = str;
        return;
    }

    int num=digits[deep]-'0';
    for (int i = 0; i < strlen(data[num]); i++)
    {
        ch[deep]=data[num][i];
        dfs(deep+1,digits,retstr);
        ch[deep]='\0';
    }
    
    return;
}

// @lc code=end

int main(void)
{
    char str[100];
    char **ret=NULL;
    int size=0;
    scanf("%s",str);
    ret=letterCombinations(str,&size);
    for (int i = 0; i < size; i++)
    {
        printf("%s\n",ret[i]);
    }
    
    return 0;
}

