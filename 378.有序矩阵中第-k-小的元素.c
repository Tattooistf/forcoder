/*
 * @lc app=leetcode.cn id=378 lang=c
 *
 * [378] 有序矩阵中第 K 小的元素
 *
 * https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/description/
 *
 * algorithms
 * Medium (63.17%)
 * Likes:    657
 * Dislikes: 0
 * Total Accepted:    78.2K
 * Total Submissions: 122.4K
 * Testcase Example:  '[[1,5,9],[10,11,13],[12,13,15]]\n8'
 *
 * 给你一个 n x n 矩阵 matrix ，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。
 * 请注意，它是 排序后 的第 k 小元素，而不是第 k 个 不同 的元素。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
 * 输出：13
 * 解释：矩阵中的元素为 [1,5,9,10,11,12,13,13,15]，第 8 小元素是 13
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：matrix = [[-5]], k = 1
 * 输出：-5
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == matrix.length
 * n == matrix[i].length
 * 1 
 * -10^9 
 * 题目数据 保证 matrix 中的所有行和列都按 非递减顺序 排列
 * 1 
 * 
 * 
 */

// @lc code=start
int func(int ** matrix, int matrixSize, int val)
{
    int num = 0;
    int j = 0;
    int i = matrixSize-1; //错误： i/j的初始值弄反了；从左下脚开始计算
    while (i >= 0 && j <= matrixSize-1)
    {
        if (matrix[i][j] <= val)
        {
            num += i+1;
            j++;
        }
        else
        {
            i--;
        }
    }
    return num;
}
// 错误：大的思路正确，使用二分法，但是对于如何求func没有想到好方法，最终看题解完成的
// 看过题解后发现出了暴力解题法，还有堆的方式，求第K大或小都可以用堆解决
int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k){
    int mid = 0;
    int left = matrix[0][0];
    int right = matrix[matrixSize-1][matrixSize-1];
    while (left <= right)
    {
        mid = left+(right-left)/2;
        if (func(matrix,matrixSize,mid) < k)
        {
            left = mid+1;
        }
        else if (func(matrix,matrixSize,mid) == k)
        {
            // break; //为什么不是break？小于等于k个可能有多个数，甚至有的数不在矩阵中，通过找最左侧数能解决问题
            right = mid - 1;
            // left = mid +1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return left;
    
}
// @lc code=end

