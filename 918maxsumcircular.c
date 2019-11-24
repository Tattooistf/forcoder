#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int A[]={1,-2,3,-2};

#define MAX 30000
int maxSubarraySumCircular(int* A, int ASize);

int main()
{
    int result=0;
    result=maxSubarraySumCircular(A, sizeof(A)/sizeof(A[0]));
    printf("%d\n",result);
    return 0;
}  
int maxnum(int a, int b)
{
    return a>b?a:b;
}

int minnum(int a, int b)
{
    return a<b?a:b;
}

int maxSubarraySumCircular(int* A, int ASize){
    int i=0;
    int maxnow=0;
    int sum=0;
    int max=-30000;
    int min=0;
    int minnow=0;

    for(i = 0; i < ASize; i++)
    {
        sum+=A[i];
        maxnow=maxnum(A[i],maxnow+A[i]);
        max=maxnum(max,maxnow);

        minnow=minnum(A[i],minnow+A[i]);
        min=minnum(min,minnow);
    }

    if (min==sum) {
        return max;
    }
    
    return maxnum(max,sum-min);
}



int maxSubarraySumCircular2(int* A, int ASize){
    int i;
    int maxsum=0;
    int minsum=0;
    int sum=0;
    int max=-30000;
    int min=0;

    if(ASize > 30000) return 0;

    for(i=0;i<ASize;i++)
    {
        maxsum=maxsum>0?maxsum+A[i]:A[i];
        max=maxsum>max?maxsum:max;

        minsum=minsum<0?minsum+A[i]:A[i];
        min=minsum<min?minsum:min;

        sum+=A[i];
    }

    if (min==sum) {
        return max;
    }
    

    if (max<(sum-min)) {
        return sum-min;
    }

    return max;
}