/*
 * @lc app=leetcode.cn id=78 lang=c
 *
 * [78] 子集
 *
 * https://leetcode-cn.com/problems/subsets/description/
 *
 * algorithms
 * Medium (76.94%)
 * Likes:    532
 * Dislikes: 0
 * Total Accepted:    78.2K
 * Total Submissions: 101.3K
 * Testcase Example:  '[1,2,3]'
 *
 * 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 
 * 说明：解集不能包含重复的子集。
 * 
 * 示例:
 * 
 * 输入: nums = [1,2,3]
 * 输出:
 * [
 * ⁠ [3],
 * [1],
 * [2],
 * [1,2,3],
 * [1,3],
 * [2,3],
 * [1,2],
 * []
 * ]
 * 
 */

// @lc code=start


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int count=0;//可以直接使用returnsize来解决但是需要新增一个参数
int value[20]={0};//可以通过申请buffer传入进去来解决，但带来参数多一个
void dfs(int level,int *nums,int size,int start,int **array,int **returnCol);
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **array=(int **)malloc(sizeof(int*)*6000);//第二次：最大值设置太小，导致最后一个用例10个元素会出现越界
    count = 0;

    dfs(0,nums,numsSize,0,array,returnColumnSizes);
    *returnSize=count;
    return array;
}

void dfs(int level,int *nums,int size,int start,int **array,int **returnCol)
{
    //if (level<=size)
    {
        int *res=(int*)malloc(sizeof(int)*level);
        memset(res,0,sizeof(int)*level);
        memcpy(res,value,sizeof(int)*level);
        *(array+count)=res;
        (*returnCol)[count]=level; //第一次二维数组指针返回值使用错误
        count++;
    }
    
    for (int i = start; i < size; i++)
    {
        value[level]=nums[i];
        dfs(level+1,nums,size,i+1,array,returnCol);
        value[level]=0;
    }
    
    return;
}

// @lc code=end

