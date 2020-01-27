#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/* 
    给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

    注意：答案中不可以包含重复的三元组。
*/
int nums[]={-7,-4,-6,6,4,-6,-9,-10,-7,5,3,-1,-5,8,-1,-2,-8,-1,5,-3,-5,4,2,-5,-4,4,7};

/*几个出错的细节点：（思路比较容易想到，但细节点丢失的太多，导致调试花了大量时间）
1、return前没有将returnsize赋值
2、去重复方法暴力，导致第一次能通过，性能表现很差
3、n个数组应该有多少个解，计算不出来，导致内存大小分配太小，出现访问异常
4、去重复的判断条件(i>0 && nums[i]==nums[i-1])将i>0放在后面导致访问异常
5、后面两个数的去重复判断条件没有加入i<j也容易导致异常
*/

//第一反应使用的暴力破解法，虽然能够做出来，但是输出结果三元组的顺序不符合预期；可以肯定是需要先排序再处理
int isDup(int **array,int size,int a,int b,int c);
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
int main(void)
{
    int size=sizeof(nums)/sizeof(nums[0]);
/*    scanf("%d\n",&size);
    int *nums=(int *)malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d",&nums[i]);
    }
    */
    int retSize=0;
    int *col=NULL;
    int **pptr=threeSum(nums,size,&retSize,&col);

    for (int i = 0; i < retSize; i++)
    {
        printf("%d,%d,%d\n",pptr[i][0],pptr[i][1],pptr[i][2]);
    }
    
    return 0;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **ppretarray=(int **)malloc(sizeof(int *)*numsSize*8);
    int *pcolsize=(int *)malloc(sizeof(int)*numsSize*8);
    int *ptr=NULL;
    *returnSize = 0;

    if (numsSize<3)
    {
        return NULL;
    }
    
    memset(ppretarray,0,sizeof(int *)*numsSize*8);
    memset(pcolsize,0,sizeof(int )*numsSize*8);

    int i,j;
    int cnt=0;
    for (i = 0; i < numsSize; i++)
    {
        for (j = i+1; j < numsSize; j++)
        {
            if (nums[i]>nums[j])
            {
                int tmp=nums[i];
                nums[i]=nums[j];
                nums[j]=tmp;
            }
        }
    }
    
    for (i = 0; i < numsSize-2; i++)
    {
        if (nums[i]>0) break;
        if(i>0 && nums[i]==nums[i-1]) continue;
        
        int left=i+1;
        int right=numsSize-1;
        while (left<right)
        {             
            if (nums[i]+nums[left]+nums[right]<0)
            {
                left++;              
            }
            else if(nums[i]+nums[left]+nums[right]>0)
            {
                right--;
            }
            else
            {
                ptr=(int *)malloc(sizeof(int)*3);
                ptr[0]=nums[i];
                ptr[1]=nums[left];
                ptr[2]=nums[right];
                pcolsize[cnt]=3;
                ppretarray[cnt++]=ptr;   
                left++;    
                right--;  
                while (left<right && nums[left]==nums[left-1])
                {
                    left++;
                }
                while (left<right && nums[right]==nums[right+1])
                {
                    right--;
                }                   
            }  
        }  
    }
    *returnSize=cnt;
    *returnColumnSizes=pcolsize;
    return ppretarray;    
}

//暴力破解法，输出结果正确，但顺序不符合要求
int** threeSum0(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **ppretarray=(int **)malloc(sizeof(int *)*numsSize);
    int *pcolsize=(int *)malloc(sizeof(int)*numsSize);
    int *ptr=NULL;

    if (numsSize<3)
    {
        return NULL;
    }
    memset(ppretarray,0,sizeof(int *)*numsSize);
    memset(pcolsize,0,sizeof(int )*numsSize);
    *returnSize = 0;

    int i,j,k;
    int cnt=0;
    for (i = 0; i < numsSize; i++)
    {
        for (j = i+1; j < numsSize; j++)
        {
            for (k = j+1; k < numsSize; k++)
            {
                if ((nums[i]+nums[j]+nums[k]) == 0 && !isDup(ppretarray,cnt,nums[i],nums[j],nums[k]))
                {
                    ptr=(int *)malloc(sizeof(int)*3);
                    ptr[0]=nums[i];
                    ptr[1]=nums[j];
                    ptr[2]=nums[k];
                    pcolsize[cnt]=3;
                    ppretarray[cnt++]=ptr;
                }
            }            
        }        
    }
    *returnSize=cnt;
    *returnColumnSizes=pcolsize;
    return ppretarray;    
}

//使用双向指针后判断条件可以直接比较一次就行，因为abc是排序的
int isDup(int **array,int size,int a,int b,int c)
{
    for (int i = 0; i < size; i++)
    {
        if ((array[i][0]==a && array[i][1]==b)
        || (array[i][0]==a && array[i][1]==c)
        || (array[i][0]==b && array[i][1]==c)
        || (array[i][0]==b && array[i][1]==a)
        || (array[i][0]==c && array[i][1]==b)
        || (array[i][0]==c && array[i][1]==a))
        {
            return 1;
        }
    }
    return 0;
}
