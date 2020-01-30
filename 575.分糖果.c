/*
 * @lc app=leetcode.cn id=575 lang=c
 *
 * [575] 分糖果
 *
 * https://leetcode-cn.com/problems/distribute-candies/description/
 *
 * algorithms
 * Easy (65.04%)
 * Likes:    54
 * Dislikes: 0
 * Total Accepted:    14.1K
 * Total Submissions: 21.7K
 * Testcase Example:  '[1,1,2,2,3,3]'
 *
 * 
 * 给定一个偶数长度的数组，其中不同的数字代表着不同种类的糖果，每一个数字代表一个糖果。你需要把这些糖果平均分给一个弟弟和一个妹妹。返回妹妹可以获得的最大糖果的种类数。
 * 
 * 示例 1:
 * 
 * 
 * 输入: candies = [1,1,2,2,3,3]
 * 输出: 3
 * 解析: 一共有三种种类的糖果，每一种都有两个。
 * ⁠    最优分配方案：妹妹获得[1,2,3],弟弟也获得[1,2,3]。这样使妹妹获得糖果的种类数最多。
 * 
 * 
 * 示例 2 :
 * 
 * 
 * 输入: candies = [1,1,2,3]
 * 输出: 2
 * 解析: 妹妹获得糖果[2,3],弟弟获得糖果[1,1]，妹妹有两种不同的糖果，弟弟只有一种。这样使得妹妹可以获得的糖果种类数最多。
 * 
 * 
 * 注意:
 * 
 * 
 * 数组的长度为[2, 10,000]，并且确定为偶数。
 * 数组中数字的大小在范围[-100,000, 100,000]内。
 * 
 * 
 * 
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start
int cmp(const void *a,const void *b)
{
    return (*(int*)a>*(int*)b);
}
// 第一次尝试使用qsort库函数，compare返回值代表升序还是降序，难以理解
// 代码比较简单，考虑清楚糖果类型数目和均分个数的关系就非常简单了。
// 逻辑就能体现为return的一句语句搞定;难得一见的一次通过
int distributeCandies(int* candies, int candiesSize){
    int count=1;
    // 先对整形数组排序，然后找出不重复的值的个数
    qsort(candies,candiesSize,sizeof(int),cmp);
    for (int i = 1; i < candiesSize; i++)
    {
        if (candies[i]!=candies[i-1])
        {
            count++;
        }
        
    }
    return (count>(candiesSize/2))?(candiesSize/2):count;    
}


// @lc code=end

int main(void)
{
    int candies[]={1,1,2,3,2,3};
    int res=0;
    res=distributeCandies(candies,sizeof(candies)/sizeof(candies[0]));
    printf("%d\n",res);
    return 0;
}
