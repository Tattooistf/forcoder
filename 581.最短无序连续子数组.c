/*
 * @lc app=leetcode.cn id=581 lang=c
 *
 * [581] 最短无序连续子数组
 *
 * https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/description/
 *
 * algorithms
 * Medium (36.03%)
 * Likes:    542
 * Dislikes: 0
 * Total Accepted:    58.6K
 * Total Submissions: 158.8K
 * Testcase Example:  '[2,6,4,8,10,9,15]'
 *
 * 给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
 * 
 * 请你找出符合题意的 最短 子数组，并输出它的长度。
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [2,6,4,8,10,9,15]
 * 输出：5
 * 解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,3,4]
 * 输出：0
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [1]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * -10^5 
 * 
 * 
 * 
 * 
 * 进阶：你可以设计一个时间复杂度为 O(n) 的解决方案吗？
 * 
 * 
 * 
 */



// @lc code=start
int comp(const void *a, const void *b)
{
    int *tmpa = (int *)a;
    int *tmpb = (int *)b;

    if (*tmpa < *tmpb)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int findUnsortedSubarray(int* nums, int numsSize){
    int *numsOrig = (int *)malloc(sizeof(int)*numsSize);
    memcpy(numsOrig,nums,sizeof(int)*numsSize);
    qsort(nums,numsSize,sizeof(int),comp);

    int start = 0;
    int end = numsSize-1;
    while ((start < end))
    {
        if (nums[end] != numsOrig[end] && nums[start] != numsOrig[start])
        {
            break;
        }
        
        if (nums[start] == numsOrig[start])
        {
            start++;
        }

        if (nums[end] == numsOrig[end])
        {
            end--;
        }
    }
    
    free(numsOrig);
    if (start == end)
    {
        return 0;
    }
    
    return end-start+1;
}
// @lc code=end

// 排序后找到位置有变化的元素，以此找到最左和最右的下标
int findUnsortedSubarray(int* nums, int numsSize){
    int *numsOrig = (int *)malloc(sizeof(int)*numsSize);
    memcpy(numsOrig,nums,sizeof(int)*numsSize);
    qsort(nums,numsSize,sizeof(int),comp);

    int start = numsSize;
    int end = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != numsOrig[i])
        {
            start = start > i?i:start;
            end = end < i?i:end;
        }
    }
    free(numsOrig);
    if (start > end)
    {
        return 0;
    }
    
    return end-start+1;
}



/* 思路完全正确，处理细节上出现了两个问题
    1、取左右最值时没有理解正确，走了弯路，误以为需要保留前次的值，只有比前次值小的时候才进行处理；
    实际上只要取前面最小的位置就行；右侧的思路也是类似；注释掉if val判断后反而一次通过；
    2、判断情况必须考虑天然满足的情况，此时ab都是初始值，需要单独处理
 */

int Stack[20000] = {0};
int Top = 0;
int Size = 0;
void InitStack(int size)
{
    memset(Stack,0,sizeof(Stack));
    Top = 0;
    Size = size;
    return;
}

void StackPush(int a)
{
    if (Top >= Size)
    {
        printf("Stack Full\n");
        return;
    }
    
    Stack[Top++] = a;
    return;
}

int StackPop(void)
{
    if (Top == 0)
    {
        printf("Stack Empty\n");
        return;
    }
    int a = Stack[--Top];  /* 容易弄错，应该是--top，前面误用了top-- */
    return a;
}

int StackTop(void)
{
    return Stack[Top-1];
}
int StackEmpty(void)
{
    return (Top == 0);
}

int findUnsortedSubarray(int* nums, int numsSize){
    int a = numsSize;
    int b = 0;
    int tmp = 0;
    // int val = 0x0fffffff;
    InitStack(numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        
        while (!StackEmpty() && nums[StackTop()] > nums[i])
        {
            tmp = StackPop();
            //if (val >= nums[i])
            {
                a = tmp>a?a:tmp;
                //val = nums[i];
            }
        }
        StackPush(i);
    }
    // printf("a = %d\n",a);

    // val = 0xffffffff;
    InitStack(numsSize);
    for (int j = numsSize-1; j >= 0; j--)
    {
        while (!StackEmpty() && nums[StackTop()] < nums[j])
        {
            tmp = StackPop();
            //if (val <= nums[j])
            {
                b = tmp>b?tmp:b;
                // val = nums[j];
            }
        }
        StackPush(j); 
    }
    // printf("b = %d\n",b);
    if (a == numsSize && b == 0)
    {
        return 0;
    }
    
    return (b-a)+1;
    
}
