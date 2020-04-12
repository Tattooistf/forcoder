/*
 * @lc app=leetcode.cn id=152 lang=c
 *
 * [152] 乘积最大子数组
 *
 * https://leetcode-cn.com/problems/maximum-product-subarray/description/
 *
 * algorithms
 * Medium (37.67%)
 * Likes:    458
 * Dislikes: 0
 * Total Accepted:    45.1K
 * Total Submissions: 119.4K
 * Testcase Example:  '[2,3,-2,4]'
 *
 * 给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字）。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 输入: [2,3,-2,4]
 * 输出: 6
 * 解释: 子数组 [2,3] 有最大乘积 6。
 * 
 * 
 * 示例 2:
 * 
 * 输入: [-2,0,-1]
 * 输出: 0
 * 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
 * 
 */

// @lc code=start

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
int maxProduct(int* nums, int numsSize){
    //int *dp=(int*)malloc(sizeof(int)*(numsSize+1));
    int res=nums[0];
    int maxnum=1,minnum=1;//1乘以任何数都等于对方，所以选择1作为初始值
    for (int i = 0; i < numsSize; i++)
    {
        if(nums[i]<0)
        {
            int temp=maxnum;
            maxnum=max(minnum*nums[i],nums[i]);
            minnum=min(temp*nums[i],nums[i]);
        }
        else
        {
            maxnum=max(maxnum*nums[i],nums[i]);
            minnum=min(minnum*nums[i],nums[i]);
        }
        res=max(maxnum,res);
    }
    //free(dp);
    return res;
}


// @lc code=end

