/*
 * @lc app=leetcode.cn id=67 lang=c
 *
 * [67] 二进制求和
 *
 * https://leetcode-cn.com/problems/add-binary/description/
 *
 * algorithms
 * Easy (51.93%)
 * Likes:    291
 * Dislikes: 0
 * Total Accepted:    58.8K
 * Total Submissions: 113.3K
 * Testcase Example:  '"11"\n"1"'
 *
 * 给定两个二进制字符串，返回他们的和（用二进制表示）。
 * 
 * 输入为非空字符串且只包含数字 1 和 0。
 * 
 * 示例 1:
 * 
 * 输入: a = "11", b = "1"
 * 输出: "100"
 * 
 * 示例 2:
 * 
 * 输入: a = "1010", b = "1011"
 * 输出: "10101"
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start
// 第一次将题目想简单了，以为简单的转换就行；后来发现需要使用先倒序再处理，完成后还要再倒序
// 调试时swap又栽在恢复的时候使用s[i]，调试花了一会功夫；解决后一次提交通过，性能100%
// 将aval类型从int修改为char后，内存提升一倍
void reverse(char *s,int len)
{
    for (int i = 0; i < len/2; i++)
    {
        char tmp=s[i];
        s[i]=s[len-i-1];
        s[len-i-1]=tmp;
    }   
    return; 
}

char * addBinary(char * a, char * b){
    int lena=strlen(a);
    int lenb=strlen(b);
    int lenm=lena>lenb?lena:lenb;
    char *res=(char *)malloc(sizeof(char)*(lenm+2));
    int carry=0;

    memset(res,0,sizeof(char)*(lenm+2));
    reverse(a,lena);
    reverse(b,lenb); 

    int i;
    char aval,bval;
    for (i = 0; i < lenm; i++)
    {
        aval=(i<lena)?(a[i]-'0'):0;
        bval=(i<lenb)?(b[i]-'0'):0;        
        res[i]=aval+bval+carry;
        carry=res[i]/2;
        res[i]=res[i]%2+'0';
    }
    if (carry)
    {
        lenm+=1;
        res[i]+=carry+'0';
    }
    reverse(res,lenm);
    
    return res;
}


// @lc code=end

int main(void)
{
    char str1[100];
    char str2[100];
    scanf("%s",&str1);
    scanf("%s",&str2);
    
    char *res=addBinary(str1,str2);
    printf("%s\n",res);
    return 0;
}
