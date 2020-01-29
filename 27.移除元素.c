/*
 * @lc app=leetcode.cn id=27 lang=c
 *
 * [27] 移除元素
 *
 * https://leetcode-cn.com/problems/remove-element/description/
 *
 * algorithms
 * Easy (57.18%)
 * Likes:    469
 * Dislikes: 0
 * Total Accepted:    127.5K
 * Total Submissions: 222.9K
 * Testcase Example:  '[3,2,2,3]\n3'
 *
 * 给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。
 * 
 * 不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
 * 
 * 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
 * 
 * 示例 1:
 * 
 * 给定 nums = [3,2,2,3], val = 3,
 * 
 * 函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。
 * 
 * 你不需要考虑数组中超出新长度后面的元素。
 * 
 * 
 * 示例 2:
 * 
 * 给定 nums = [0,1,2,2,3,0,4,2], val = 2,
 * 
 * 函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。
 * 
 * 注意这五个元素可为任意顺序。
 * 
 * 你不需要考虑数组中超出新长度后面的元素。
 * 
 * 
 * 说明:
 * 
 * 为什么返回数值是整数，但输出的答案是数组呢?
 * 
 * 请注意，输入数组是以“引用”方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
 * 
 * 你可以想象内部操作如下:
 * 
 * // nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
 * int len = removeElement(nums, val);
 * 
 * // 在函数里修改输入数组对于调用者是可见的。
 * // 根据你的函数返回的长度, 它会打印出数组中该长度范围内的所有元素。
 * for (int i = 0; i < len; i++) {
 * print(nums[i]);
 * }
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
// @lc code=start

// 第一次理解错误，直接使用前后交换的方式来处理：几个特殊场景上没考虑清楚
// 1、right都是重复数字的情况
// 2、223这种会导致left和right相同的情况
// 调试通过后才发现第一次直接全部遍历，不相等的从前到后重新存储就行，简单3行语句搞定
int removeElement(int* nums, int numsSize, int val){
    int tmp=0;

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i]!=val)
        {
            nums[tmp++]=nums[i];
        }
    }
    return tmp;
}

int removeElement0(int* nums, int numsSize, int val){
    int left=0,right=numsSize-1;
    int ret=numsSize;

    if (numsSize<1 || (numsSize==1 && nums[0]==val))
    {
        return 0;
    }
    while (nums[right]==val)
    {
        right--;
        ret--;
        if (ret==0)
        {
            return 0;
        }
    }    

    while (left<right)
    {      
        if (nums[left]==val)
        {
            int tmp=nums[left];
            nums[left]=nums[right];
            nums[right]=tmp;
            right--;
            ret--;
            while (right>0 && nums[right]==val)
            {
                right--;
                ret--;
            }                          
        }
        left++;
    }    
    return ret;
}

// @lc code=end

int array[]={3,2,1,3};
int val=3;
int main(void)
{
    int result = 0;
    result = removeElement(array,sizeof(array)/sizeof(array[0]),val);
    for (int i = 0; i < result; i++)
    {
        printf("%d",array[i]);
        if (i<result-1)
        {
            printf(", ");
        }
    }
    
    return 0;
}
