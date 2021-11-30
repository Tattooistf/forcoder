/*
 * @lc app=leetcode.cn id=658 lang=c
 *
 * [658] 找到 K 个最接近的元素
 *
 * https://leetcode-cn.com/problems/find-k-closest-elements/description/
 *
 * algorithms
 * Medium (44.53%)
 * Likes:    251
 * Dislikes: 0
 * Total Accepted:    26.2K
 * Total Submissions: 57.7K
 * Testcase Example:  '[1,2,3,4,5]\n4\n3'
 *
 * 给定一个排序好的数组 arr ，两个整数 k 和 x ，从数组中找到最靠近 x（两数之差最小）的 k 个数。返回的结果必须要是按升序排好的。
 * 
 * 整数 a 比整数 b 更接近 x 需要满足：
 * 
 * 
 * |a - x| < |b - x| 或者
 * |a - x| == |b - x| 且 a < b
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：arr = [1,2,3,4,5], k = 4, x = 3
 * 输出：[1,2,3,4]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：arr = [1,2,3,4,5], k = 4, x = -1
 * 输出：[1,2,3,4]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 数组里的每个元素与 x 的绝对值不超过 10^4
 * 
 * 
 */

// @lc code=start

// 错误：完全没有想到二分法的具体解题方法
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize){
    int left = 0;
    int right = arrSize-k;

    while (left < right)
    {
        int mid = left+(right-left)/2;
        if (x-arr[mid] <= arr[mid+k]-x) // 考虑寻找最小值，应该找最左值
        {
            right = mid;
        }
        else
        {
            left = mid+1;
        }
    }
    // printf("%d",left);
    int *ret = (int *)malloc(sizeof(int)*k);
    memcpy(ret,arr+left,sizeof(int)*k);
    *returnSize = k;
    return ret;
}
// @lc code=end

