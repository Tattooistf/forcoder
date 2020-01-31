/*
 * @lc app=leetcode.cn id=283 lang=c
 *
 * [283] 移动零
 *
 * https://leetcode-cn.com/problems/move-zeroes/description/
 *
 * algorithms
 * Easy (58.86%)
 * Likes:    480
 * Dislikes: 0
 * Total Accepted:    101K
 * Total Submissions: 171.4K
 * Testcase Example:  '[0,1,0,3,12]'
 *
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 
 * 示例:
 * 
 * 输入: [0,1,0,3,12]
 * 输出: [1,3,12,0,0]
 * 
 * 说明:
 * 
 * 
 * 必须在原数组上操作，不能拷贝额外的数组。
 * 尽量减少操作次数。
 * 
 * 
 */

// @lc code=start

// 第一次想法直接赋值，遗漏最后非零的值挪走后未清零
// 第二次想使用最高效的清零方式，全非零数组的情况未考虑，导致解答错误
// 第三次修正后通过，效率不高，后来通过挪出来重新清零解决。
void moveZeroes(int* nums, int numsSize){
    int i=0,j=0;
    for (i = 0; i < numsSize; i++)
    {
        if(nums[i]!=0)
        {
            nums[j++]=nums[i];
            //if(i!=j-1) nums[i]=0;
        }
    }

    for (i = j; i < numsSize; i++)
    {
        nums[i]=0;
    }
    
    return;    
}


// @lc code=end

int main(void)
{
    int nums[]={0,1,3,0,12};
    int count = sizeof(nums)/sizeof(nums[0]);
    moveZeroes(nums,count);
    for (int i = 0; i < count; i++)
    {
        printf("%d",nums[i]);
        if (i!=count-1)
        {
            printf(",");
        }        
    }
    
    return 0;
}