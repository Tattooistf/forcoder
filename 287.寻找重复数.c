/*
 * @lc app=leetcode.cn id=287 lang=c
 *
 * [287] 寻找重复数
 *
 * https://leetcode-cn.com/problems/find-the-duplicate-number/description/
 *
 * algorithms
 * Medium (66.37%)
 * Likes:    1377
 * Dislikes: 0
 * Total Accepted:    173.1K
 * Total Submissions: 261.3K
 * Testcase Example:  '[1,3,4,2,2]'
 *
 * 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
 * 
 * 假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。
 * 
 * 你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,3,4,2,2]
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [3,1,3,4,2]
 * 输出：3
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [1,1]
 * 输出：1
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：nums = [1,1,2]
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * nums.length == n + 1
 * 1 
 * nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
 * 
 * 
 * 
 * 
 * 进阶：
 * 
 * 
 * 如何证明 nums 中至少存在一个重复的数字?
 * 你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？
 * 
 * 
 */

// @lc code=start

int findDuplicate(int* nums, int numsSize){
    int slow = 0;
    int fast = 0;

    do
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    
    slow = 0;
    while (slow != fast)
    {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}
// @lc code=end



#define MAX(a,b) ((a)>(b)?(a):(b))
int findDuplicate(int* nums, int numsSize){
    // int max = 0;
    // for (int i = 0; i < numsSize; i++)
    // {
    //     max = MAX(max,nums[i]);
    // }
    
    int *arr = (int *)malloc(sizeof(int)*(numsSize+1));
    memset(arr,0,sizeof(int)*(numsSize+1));
    for (int i = 0; i < numsSize; i++)
    {
        arr[nums[i]]++;
    }

    for (int i = 0; i < numsSize+1; i++)
    {
        if (arr[i] > 1)
        {
            return i;
        }
    }
    free(arr);
    return 0;
}