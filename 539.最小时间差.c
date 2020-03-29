/*
 * @lc app=leetcode.cn id=539 lang=c
 *
 * [539] 最小时间差
 *
 * https://leetcode-cn.com/problems/minimum-time-difference/description/
 *
 * algorithms
 * Medium (52.59%)
 * Likes:    42
 * Dislikes: 0
 * Total Accepted:    4.5K
 * Total Submissions: 8.4K
 * Testcase Example:  '["23:59","00:00"]'
 *
 * 给定一个 24 小时制（小时:分钟）的时间列表，找出列表中任意两个时间的最小时间差并已分钟数表示。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入: ["23:59","00:00"]
 * 输出: 1
 * 
 * 
 * 
 * 备注:
 * 
 * 
 * 列表中时间数在 2~20000 之间。
 * 每个时间取值在 00:00~23:59 之间。
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start

#define MAX_MIN (60*24)
int covert(char *s)
{
    // if(strlen(s)!=5 || s[2]!=':') return 0;
    int hour=(s[0]-'0')*10+s[1]-'0';
    int min=(s[3]-'0')*10+s[4]-'0';
    return (hour*60+min);
}

int findMinDifference(char ** timePoints, int timePointsSize){
    int *array=(int *)malloc(sizeof(int)*MAX_MIN);
    int min=MAX_MIN;
    memset(array,0,sizeof(int)*MAX_MIN);

    if(timePointsSize>MAX_MIN) return 0;//每一个时刻都至少有1个，说明有重复

    for (int i = 0; i < timePointsSize; i++)
    {
        if(strlen(timePoints[i])!=5 || timePoints[i][2]!=':') return 0;
        int val=covert(timePoints[i]);
        if(array[val]==1) return 0;//说明有重复的时间
        array[val]++;
    }
    int count=1;
    int i=0;
    while (array[i]==0) //先找到第一个不为零的
    {
        i++;
    }
    i=i+1;//跳过第一个非零
    for (; i < 2*MAX_MIN; i++)
    {
        if(array[i%MAX_MIN]==0)
        {
            count++;
        }
        else
        {
            min=(count<min)?count:min;
            count=1;
        }  
    }
    
    free(array);
    return min;
}


// @lc code=end
char A[]="23:59";
char B[]="00:00";
char *str[]={A,B};

int main(void)
{
    // char *str[]={"23:59","00:00"};
    int ret=findMinDifference(str,sizeof(str)/sizeof(str[0]));
    return 0;
}
