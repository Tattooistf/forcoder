#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int A[]={4,2,3,1};

int maxWidthRamp(int* A, int ASize);

int main()
{
    int result=0;
    result=maxWidthRamp(A, sizeof(A)/sizeof(A[0]));
    printf("%d\n",result);
    return 0;
}  
//单调栈（递减）从后往前遍历：直观理解建立栈存储的是宽度的底部
int maxWidthRamp(int* A, int ASize){
    int i=0;
    int index[50000]={0};
    int max=0;
    int cnt=0;

    index[cnt++]=0;
    //printf("%d:%d\n",0,A[0]);
    for( i = 1; i < ASize; i++)
    {
        if (A[i]<A[index[cnt-1]]) {
            index[cnt++]=i;
            //printf("%d:%d\n",i,A[i]);
        }
        
    }

    for(i = ASize-1; i >=0; i--)
    {
        if (i<max) {
            break;
        }
        
        while((cnt>=1)&&(A[i]>=A[index[cnt-1]])){
            if (i>max) {
                max=(i-index[cnt-1])>max?(i-index[cnt-1]):max;    
            }
            cnt--;
        }
        index[cnt++]=i;
        
    }
    return max;
}

#if 0
//maximum-width-ramp 递归查询法-超出时间限制
int search(int start,int end);

int maxWidthRamp(int* A, int ASize){
    int start=0;
    int end=0;
    int max=0;
    int len=0;
    if ((ASize<2)||(ASize>50000)) {
        return 0;
    }
    end = ASize-1;
    while(start<end){
        len = search(start,end);
        max=max>len?max:len;
        start++;
        end--;
    }
    
    return max;
}

int search(int start,int end)
{
    int a,b;
    int max=0;
    a=start;
    b=end;
    while(a<b){
        if (A[a]>A[b]) {
            a++;
        }
        else
        {
            max=(max>(b-a))?max:(b-a);
            b--;
        }
    }

    a=start;
    b=end;
    while(a<b){
        if (A[a]>A[b]) {
            b--;
        }
        else
        {
            max=(max>(b-a))?max:(b-a);
            a++;
        }
    }       
    return max;
}
#endif

#if 0
//动态规划法-超出内存限制
//maximum-width-ramp
int maxnum(int a,int b)
{
    return a>b?a:b;
}

int maxWidthRamp(int* A, int ASize){
    int i=0;
    int j=0;
    int max=0;
    int len=0;
    if ((ASize<2)||(ASize>50000)) {
        return 0;
    }

    int **B=(int **)malloc(ASize*sizeof(int *));
    if (B==NULL) {
        return 0;
    }

    for(int i = 0; i < ASize; i++)
    {
        B[i]=(int *)malloc(ASize*sizeof(int));
        memset(B[i],0,ASize*sizeof(int));
    }

    for(i = ASize-2; i >=0; i--)
    {   
        for( j = i; j < ASize; j++)
        {
            if (A[i]>A[j]) {
                B[i][j]=maxnum(B[i+1][j],B[i][j-1]);
            }
            else
            {
                B[i][j]=j-i;
            }
        }
        
    }
    max=B[0][ASize-1];
    
    for(int i = 0; i < ASize; i++)
    {
        free(B[i]);
        B[i]=NULL;
    }   
    free(B);
    B=NULL;
    
    return max;
}

//数组大小排序，利用数组下标计算最大宽度
int maxWidthRamp(int* A, int ASize){
    int i=0;
    int j=0;
    int tmp=0;
    int max;

    int *B=malloc(ASize*sizeof(int));
    if(B==NULL) return 0;
    for( i = 0; i < ASize; i++)
    {
        B[i]=i;
    }

    
    for( i = 0; i < ASize; i++)
    {
        for( j = i+1; j < ASize; j++)
        {
            if((A[B[i]]==A[B[j]])&&(B[i]>B[j]))
            {
                tmp=B[i];
                B[i]=B[j];
                B[j]=tmp;
                continue;
            }
            if((A[B[i]]>A[B[j]]))
            {
                tmp=B[i];
                B[i]=B[j];
                B[j]=tmp;
            }
            
        }
        
    }

    for( i = 0; i < ASize; i++)
    {
        printf("%d-",B[i]);;
    }    
    
    max=0;
    #if 0
    for( i = 0; i < ASize; i++)
    {
        for( j = i+1; j < ASize; j++)
        {
            if (B[i]<B[j]) {
                max=maxnum(max,(B[j]-B[i]));
            }
        }
        
    }
    #endif

    int t=B[0];
    for( i = 0; i < ASize; i++)
    {
        max=maxnum(max,B[i]-t);
        t=t>B[i]?B[i]:t;
    }
    
    
    free(B);
 
    return max;
}
#endif