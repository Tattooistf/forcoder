#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/*  
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
你的算法时间复杂度必须是 O(log n) 级别。
如果数组中不存在目标值，返回 [-1, -1]。

示例 1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]

示例 2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
 */
int A[]={5,7,7,8,8,10};
int target=7;

int* searchRange(int* nums, int numsSize, int target, int* returnSize);
int bisearch(int *nums,int numsSize,int val,int dir);
int main(void)
{
    int *point=NULL;
    int size=0;
    point=searchRange(A,sizeof(A)/sizeof(A[0]),target,&size);
    printf("[%d, %d]\n",point[0],point[1]);
    return 0;
}
int bisearch(int *nums,int numsSize,int val,int dir);
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    //解题思路：貌似以前看到过类似的题目，直接采用二分查找，通过查找条件的不一样找到最小和最大的边界
    //算法不是最优，最后解答的思路正确，性能也还不错，但判断条件考虑的太过于繁琐，后面要优化
    int *ptr=(int *)malloc(sizeof(int)*2);
    ptr[0]=ptr[1]=-1;
    ptr[0]=bisearch(nums,numsSize,target,0);
    ptr[1]=bisearch(nums,numsSize,target,1);
    *returnSize=2;
    return ptr;
}


int bisearch(int *nums,int numsSize,int val,int dir)
{
    int left=0;
    int right=numsSize-1;

    while (left<=right)
    {
        int middle=(left+right)/2;
        if (nums[middle]==val)
        {
            if (dir==1)
            {
                if (middle==numsSize-1)//边界
                {
                    return middle;
                }
                
                if (nums[middle+1]>val)
                {
                    return middle;
                }
                left=middle+1;
            }
            else
            {
                if (middle==0)//边界
                {
                    return middle;
                }
                
                if (nums[middle-1]<val)
                {
                    return middle;
                }
                right=middle-1;
            }
            continue;        
        }
        
        if (nums[middle]>val)
        {
            right=middle-1;
        }
        else
        {
            left=middle+1;
        }       
    }
    
    return -1;
}



