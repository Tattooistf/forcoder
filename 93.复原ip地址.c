/*
 * @lc app=leetcode.cn id=93 lang=c
 *
 * [93] 复原IP地址
 *
 * https://leetcode-cn.com/problems/restore-ip-addresses/description/
 *
 * algorithms
 * Medium (45.40%)
 * Likes:    209
 * Dislikes: 0
 * Total Accepted:    30.6K
 * Total Submissions: 66.3K
 * Testcase Example:  '"25525511135"'
 *
 * 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
 * 
 * 示例:
 * 
 * 输入: "25525511135"
 * 输出: ["255.255.11.135", "255.255.111.35"]
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include "math.h"
// @lc code=start

void dfs(int level,char *s,char **result,int *returnSize,int point);
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** restoreIpAddresses(char * s, int* returnSize){
    int i=0;
    char tmp[16]={0};
    char **result=(char **)malloc(sizeof(char *)*27);
    memset(result,0,sizeof(char *)*27);

    if (strlen(s)>12 || strlen(s)<4)
    {
        *returnSize=0;
        return NULL;
    }

    dfs(1,s,result,returnSize,0);
    
    return result;
}

char res[16]={0};

void dfs(int level,char *s,char **result,int *returnSize,int point)
{
    int tmp=0;
    if (level==4)
    {
        tmp=atoi(s);
        if (tmp>255 || tmp<0)
        {
            return; //没有正确的解
        }
        strcpy(res+point,s);
        res[point+strlen(s)]='\0';
        char *str=(char *)malloc(sizeof(char)*strlen(res));
        strcpy(str,res);
        result[*returnSize]=str;
        (*returnSize)++;
        return;
    }

    for (int i = 1; i < 4; i++)
    {
        if(i>strlen(s)) return;
        char ctmp[4]={0};
        memcpy(ctmp,s,i);
        if (atoi(ctmp)>255 || atoi(ctmp)<0)
        {
            return;
        }
        memcpy(res+point,s,i);      
        dfs(level+1,s+i,result,returnSize,point+i);
        memset(res+point,0,i);
    }
    
    return;
}

// @lc code=end
int main(void)
{
    char *test="1111";
    int count =0;
    char **res=restoreIpAddresses(test,&count);
    return 0;
}
