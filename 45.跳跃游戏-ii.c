/*
 * @lc app=leetcode.cn id=45 lang=c
 *
 * [45] 跳跃游戏 II
 *
 * https://leetcode-cn.com/problems/jump-game-ii/description/
 *
 * algorithms
 * Hard (38.44%)
 * Likes:    1079
 * Dislikes: 0
 * Total Accepted:    166.1K
 * Total Submissions: 396.8K
 * Testcase Example:  '[2,3,1,1,4]'
 *
 * 给你一个非负整数数组 nums ，你最初位于数组的第一个位置。
 * 
 * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 
 * 你的目标是使用最少的跳跃次数到达数组的最后一个位置。
 * 
 * 假设你总是可以到达数组的最后一个位置。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [2,3,1,1,4]
 * 输出: 2
 * 解释: 跳到最后一个位置的最小跳跃数是 2。
 * 从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [2,3,0,1,4]
 * 输出: 2
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 1 
 * 0 
 * 
 * 
 */

// @lc code=start

// 利用内存换性能，先将是否可达全部遍历出来保存,失败
#define MAX(a,b) ((a)>(b)?(a):(b))

int jump(int* nums, int numsSize){
    int max = 0;
    int next = 0;
    int cnt = 0;
    
    for (int i = 0; i < numsSize; )
    {
        if (i <= max)
        {
            // 贪心法：从可达集中找到最远的值,实际上不用判断可达，因为每次都是取范围内跳最远的，一定是最后解
            next = MAX(next, i+nums[i]);
            i++;
            continue;
        }
        else
        {
            max = next;
            cnt++;
        }
    }
    return cnt;
}
// @lc code=end

#define MAX(a,b) ((a)>(b)?(a):(b))

int valid(int *nums, int size, int m)
{
    int max = m;
    for (int i = m; i < size; i++)
    {
        if (i <= max)
        {
            max = MAX(max, nums[i]+i);
            if (max >= size-1)
            {
                return true;
            }
        }
    }
    return false;
}

int jump(int* nums, int numsSize){
    int max = 0;
    int next = 0;
    int cnt = 0;
    for (int i = 0; i < numsSize; )
    {
        if (i <= max)
        {
            if(valid(nums,numsSize,i)) // 贪心法：从可达集中找到最远的值
            {
                next = MAX(next, i+nums[i]);
            }
            i++;
            continue;
        }
        else
        {
            max = next;
            cnt++;
        }
    }
    return cnt;
}