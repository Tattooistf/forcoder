#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int A[]={3,1,2,4};
int B[]={3,2,1,4,7};

int sumSubarrayMins(int* A, int ASize);

int main()
{
    int result=0;
    result=sumSubarrayMins(A,sizeof(A)/sizeof(A[0]));
    printf("%d\n",result);
    return 0;
}  
//个人喜欢方法2
//3.双向栈 思想：i的贡献为以i为最小值的所有数组之和，i数组找到最左和最右比i小的值，数组的个数i-left * right-i
int sumSubarrayMins(int* A, int ASize){
    int stack[30000]={0};
    int i=0;
    int left[30000]={-1};
    int right[30000]={-1};
    int count=0;
    int ans=0;

    stack[count++]=0;
    for( i = 1; i < ASize; i++)
    {
        left[i]=-1;
        while(count>0 && (A[i]<=A[stack[count-1]])){
            count--;
        }
        left[i]=count>0?stack[count-1]:(-1);
        stack[count++]=i;
    }

    count = 0;
    right[ASize-1]=ASize;
    stack[count++]=ASize-1;
    for( i = ASize-2; i >=0; i--)
    {
        right[i]=ASize;
        while(count>0 && (A[i]<A[stack[count-1]])){
            count--;
        }
        right[i]=count>0?stack[count-1]:(ASize);
        stack[count++]=i;
    }   

    for( i = 0; i < ASize; i++)
    {
        ans+=A[i]*(i-left[i])*(right[i]-i);
        ans%=1000000007;
    }
    
    return ans;
}


//2.单调递减栈  思想：i-j贡献为最小值乘以长度的累加，增加j+1变化分两种情况，其一j+1大于j直接相加，其二否则j出栈刷新最小值
//907 sum-of-subarray-minimums
#define MAX 30000
int sumSubarrayMins(int* A, int ASize){
    int stack[MAX]={0};
    int i=0;
    int count=0;
    int sum=0;
    int tmp =0;
    int ans=0;
    int len=0;

    stack[count++]=0;
    ans=sum = A[0];
    for( i = 1; i < ASize; i++)
    {
        while(count>0 && A[i]<A[stack[count-1]]){
            tmp=stack[count-1];
            count--;
            len=count>0?(tmp-stack[count-1]):(tmp+1);
            sum-=A[tmp]*len;
        }
        len=count>0?(i-stack[count-1]):(i+1);
        sum+=A[i]*len;
        stack[count++]=i;
        ans+=sum;
        ans%=1000000007;
        
    }
    
    return ans;
}

//1.暴力破解法 超时
//907 sum-of-subarray-minimums
int sumSubarrayMins1(int* A, int ASize){
    int i,j;
    int min=0;
    int sum=0;

    if (ASize==0) {
        return 0;
    }

    for( i = 0; i < ASize; i++)
    {
        min=A[i];
        sum+=min;
        for( j = i+1; j < ASize; j++)
        {
            min=A[j]<min?A[j]:min;
            sum=(sum+min)%1000000007;
        }
        
    }
    
    return sum;
}


