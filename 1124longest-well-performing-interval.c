#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"


int A[]={6,6,9};

int longestWPI(int* hours, int hoursSize);

int main()
{
    int result = 0;
    result=longestWPI(A,sizeof(A)/sizeof(A[0]));
    printf("%d \n",result);

    return 0;
}  
//前缀和+单调栈解法；另外还有一种纯前缀和的解法，技巧性很强
int longestWPI(int* hours, int hoursSize){
    int sum=0;
    int presum[10001]={0};
    int stack[10001]={0};
    int top=0;
    int i;
    int max=0;

    stack[top++]=0;
    for(i = 0; i < hoursSize; i++)
    {
        //建立前缀和数组
        presum[i]=sum;
        if (hours[i]>8) {
            sum+=1;
        }else
        {
            sum+=-1;
        }
        //建立单调递减栈
        if (presum[i]<presum[stack[top-1]]) {
            stack[top++]=i;
        }
    }
    presum[i]=sum; //注意：需要比size多用1个单元

    for(i = hoursSize; i >= 0; i--)
    {
        while((top>0)&&(presum[i]>presum[stack[top-1]])){
            max=(i-stack[top-1])>max?(i-stack[top-1]):max;
            top--;
        }
        
    }
    
    
    return max;
}

//暴力破解法 同时通过max优化，通过率91/98
int longestWPI1(int* hours, int hoursSize){
    int i;
    int good=0;
    int bad=0;
    int max=0;

    for ( i = 0; i+max < hoursSize; i++)
    {
        good=bad=0;
        for (int j = i; j < hoursSize; j++)
        {
            if (hours[j]>8)
            {
                good++;
            }
            else
            {
                bad++;
            }

            if (good>bad)
            {
                max=(j-i+1)>max?(j-i+1):max;
            }
            
            //max=(good>bad)?(j-i+1):max;            
        }
    }
    
    return max;
}


