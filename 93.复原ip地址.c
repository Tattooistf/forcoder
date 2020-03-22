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

char res[16]={0};
void dfs(int level,char *s,char **result,int *returnSize,int point);
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** restoreIpAddresses(char * s, int* returnSize){
    int i=0;
    char tmp[16]={0};
    char **result=(char **)malloc(sizeof(char *)*27);
    memset(result,0,sizeof(char *)*27);
    memset(res,0,sizeof(res));

    if (strlen(s)>12 || strlen(s)<4)
    {
        *returnSize=0;
        return NULL;
    }
    *returnSize=0;
    dfs(1,s,result,returnSize,0);
    
    return result;
}

int checkvalid(char *s)
{
    int inter=atoi(s);
    int interlen=0;
    int tmpinter=inter;

    while (tmpinter)
    {
        tmpinter/=10;
        interlen++;
    }
    
    if (inter>255 || inter<0 ||(strlen(s)>1 && interlen<strlen(s)))//排除01，00这样的情况
    {
        return 0; //没有正确的解
    }
    return 1;     
}

void dfs(int level,char *s,char **result,int *returnSize,int point)
{
    int tmp=0;
    int len=strlen(s);
    if (level==4)
    {
        if (!checkvalid(s) || len==0)
        {
            return; //没有正确的解
        }
        strcpy(res+point,s);
        res[point+len]='\0';
        char *str=(char *)malloc(sizeof(char)*(strlen(res)+1));//第一次掉坑没后+1导致访问异常
        strcpy(str,res);
        //printf("%s\n",str);
        result[*returnSize]=str;//第二次掉坑returnSize没有给初值，再次异常
        (*returnSize)++;
        return;
    }

    for (int i = 1; i < 4; i++)
    {
        if(i>len) return;
        if((len-i)>(4-level)*3) continue;//剩余的层级最大长度如果小于str的长度，说明肯定没有解
        char ctmp[4]={0};
        memcpy(ctmp,s,i);
        if (!checkvalid(ctmp))
        {
            return;
        }
        //printf("level %d,i %d\n",level,i);
        memcpy(res+point,s,i);      
        res[point+i]='.';
        dfs(level+1,s+i,result,returnSize,point+i+1);
        memset(res+point,0,i+1);//+1是包含了分隔符.的空间
    }
    
    return;
}

// @lc code=end
int main(void)
{
    char *test="010010";
    int count =0;
    char **res=restoreIpAddresses(test,&count);
    return 0;
}