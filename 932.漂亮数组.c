/*
 * @lc app=leetcode.cn id=932 lang=c
 *
 * [932] 漂亮数组
 *
 * https://leetcode-cn.com/problems/beautiful-array/description/
 *
 * algorithms
 * Medium (60.28%)
 * Likes:    125
 * Dislikes: 0
 * Total Accepted:    6.8K
 * Total Submissions: 11.1K
 * Testcase Example:  '4'
 *
 * 对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，使得：
 * 
 * 对于每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]。
 * 
 * 那么数组 A 是漂亮数组。
 * 
 * 
 * 
 * 给定 N，返回任意漂亮数组 A（保证存在一个）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：4
 * 输出：[2,1,4,3]
 * 
 * 
 * 示例 2：
 * 
 * 输入：5
 * 输出：[3,1,2,5,4]
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= N <= 1000
 * 
 * 
 * 
 * 
 */

// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/* 
 * 采用分治法进行求解，按照奇数偶数进行分治，分完后按照奇偶进行合并；大小直接为需要的大小
 * 对比两个方法发现，数字规律实际上就是正向的分治法；而分治法就是不断的递归，效率会比较低；
 */
int* beautifulArray(int n, int* returnSize){
    int leftsize = 0;
    int rightsize = 0;
    if (n == 1)
    {
        int *ret = (int *)malloc(sizeof(int)*1);
        ret[0] = 1;
        *returnSize = 1;
        return ret;
    }
    
    int *leftret = beautifulArray((n+1)/2,&leftsize);
    int *rightret = beautifulArray(n/2,&rightsize);
    int *ret = (int *)malloc(sizeof(int)*(leftsize+rightsize));
    int len = 0;
    for (int i = 0; i < leftsize; i++)
    {
        ret[len++] = leftret[i]*2-1;
    }

    for (int i = 0; i < rightsize; i++)
    {
        ret[len++] = rightret[i]*2;
    }
    free(leftret);
    free(rightret);
    *returnSize = len;
    
    return ret;
}
// @lc code=end


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/* 
 * 主要还是数字规律，分为奇数和偶数两部分，奇数满足漂亮要求，则整体进行加减也满足要求
 * 同时奇数和偶数相加肯定不满足2*A的要求，所以按照奇数一堆和偶数一堆来处理
 * 
 */
int* beautifulArray(int n, int* returnSize){
    int* ret = (int *)malloc(sizeof(int)*n);
    int *orin = (int *)malloc(sizeof(int)*n);
    if (ret == NULL || orin == NULL)
    {
        return ret;
    }
    memset(ret,0,sizeof(int)*n);
    memset(orin,0,sizeof(int)*n);

    int size = 1;
    ret[0] = 1;
    while(size < n)
    {
        int len = 0;
        memcpy(orin,ret,sizeof(int)*size);
        int i = 0;
        for (i = 0; i < 2*size; i++)
        {
            if (i>=size)
            {
                if (2*orin[i%size] <= n) /* 前面理解错误，这个地方判断数据<=n,数据大于n的就丢弃，而不需要判断size和n的大小 */
                {
                    ret[len++] = 2*orin[i%size];
                    //len++;
                }
            }
            else
            {
                if ((2*orin[i%size]-1) <= n)
                {
                    ret[len++] = 2*orin[i%size]-1;
                    //len++;
                }
            }
        }
        size = len;
    }
    *returnSize = size;
    free(orin);

    return ret;
}