#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int A[]={};

int find132pattern(int* nums, int numsSize);

int main()
{
    int result=0;
    result=find132pattern(A, sizeof(A)/sizeof(A[0]));
    printf("%d\n",result);
    return 0;
}  

//单调栈解法：从后往前寻找局部斜坡，即最大和次大数
//132-pattern
int find132pattern(int* nums, int numsSize){
    int i=0;
    int top=0;
    int stack[100]={0};
    int secmax=0x80000000;
    if(numsSize<1) return 0;
    stack[top++]=nums[numsSize-1];
    for( i = numsSize-2; i >=0; i--)
    {
        if (secmax>nums[i]) {
            return 1;
        }
        
        while((top>=1)&&(nums[i]>stack[top-1]))
        {
            secmax=secmax<stack[top-1]?stack[top-1]:secmax;
            top--;
        }
        stack[top++]=nums[i];
    }
    return 0;
}

