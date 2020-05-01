/*
 * @lc app=leetcode.cn id=113 lang=c
 *
 * [113] 路径总和 II
 *
 * https://leetcode-cn.com/problems/path-sum-ii/description/
 *
 * algorithms
 * Medium (58.98%)
 * Likes:    211
 * Dislikes: 0
 * Total Accepted:    44.1K
 * Total Submissions: 74.5K
 * Testcase Example:  '[5,4,8,11,null,13,4,7,2,null,null,5,1]\n22'
 *
 * 给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
 * 
 * 说明: 叶子节点是指没有子节点的节点。
 * 
 * 示例:
 * 给定如下二叉树，以及目标和 sum = 22，
 * 
 * ⁠             5
 * ⁠            / \
 * ⁠           4   8
 * ⁠          /   / \
 * ⁠         11  13  4
 * ⁠        /  \    / \
 * ⁠       7    2  5   1
 * 
 * 
 * 返回:
 * 
 * [
 * ⁠  [5,4,11,2],
 * ⁠  [5,8,4,5]
 * ]
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


  void doing(struct TreeNode *root,int sum,int level,int **retarray,int *returnSize,int** returnCol,int *array);
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    if (root==NULL)
    {
        return NULL;
    }
    int *array=(int *)malloc(sizeof(int)*1000);
    memset(array,0,sizeof(int)*1000);
    int **retarray=(int **)malloc(sizeof(int *)*1000);
    memset(retarray,0,sizeof(int*)*1000);
    doing(root,sum,0,retarray,returnSize,returnColumnSizes,array);

    return retarray;
   
}

void doing(struct TreeNode *root,int sum,int level,int **retarray,int *returnSize,int** returnCol,int *array)
{
    if (root->left != NULL || root->right != NULL)    
    {
        sum-=root->val;
        if (root->left != NULL)
        {
            array[level]=root->val;
            doing(root->left,sum,level+1,retarray,returnSize,returnCol,array);
            array[level]=0;
        }
        if (root->right != NULL)
        {
            array[level]=root->val;
            doing(root->right,sum,level+1,retarray,returnSize,returnCol,array);
            array[level]=0;
        }
    }
    else
    {
        if (root->val == sum)
        {
            array[level]=sum;
            //printf("%d\n",sum);
            int *tmp=(int *)malloc(sizeof(int)*(level+1));
            memset(tmp,0,sizeof(int)*(level+1));
            memcpy(tmp,array,sizeof(int)*(level+1));
            retarray[*returnSize]=tmp;
            (*returnCol)[(*returnSize)++]=level+1;
        }
    }
    return;
}

// @lc code=end

