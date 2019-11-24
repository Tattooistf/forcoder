#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int a0[]={1,1};
int a1[]={2};
int a2[]={1,1};

int *A[]={
    a0,
    a1,
    a2
};

int B[]={
    2,
    1,
    2
};

int leastBricks(int** wall, int wallSize, int* wallColSize);

int main()
{
    int result=0;
    int out;
    result=leastBricks(A,sizeof(B)/sizeof(B[0]),B);
    printf("%d",result);
    return 0;
}  

int leastBricks(int** wall, int wallSize, int* wallColSize)
{
    int i,j;
    int resCol[20000]={0};
    int sum=0;
    int result=0;
    int cnt=0;
    int num=0;

    for(i=0;i<wallSize;i++)
    {
        sum=0;
        for(j=0;j<wallColSize[i]-1;j++)
        {
            sum+=wall[i][j];
            resCol[num++]=sum;
        }
    }

    for(j=0;j<num;j++)
    {
        printf("%d\n",resCol[j]);
        cnt=1;
        for(i=j+1,cnt=0;i<num;i++)
        {
            if(resCol[i]==resCol[j]) cnt++;
        }
        result=result>cnt?result:cnt;
    }
    
    return wallSize-result;
}

int leastInterval(char* tasks, int tasksSize, int n){
    char num[26][2]={0};
    int i,k;
    int j=0;
    int cnt=0;
    char res[10000]={'0'};
    char tmp[2]={0};
    
    for(i=0;i<tasksSize;i++)
    {
        for(k=0;k<cnt;k++)
        {
            if(num[k][0] == tasks[i]) {num[k][1]++;break;}
        }
        if(k>=cnt)
        {
            num[k][0]=tasks[i];
            num[k][1]++;
            cnt++;
        }
    }

    for(i=0;i<cnt;i++)
    {
        for(k=i+1;k<cnt;k++)
        {
            if(num[k][1]>num[i][1])
            {
                tmp[1]=num[i][1];
                num[i][1]=num[k][1];
                num[k][1]=tmp[1];
                tmp[0]=num[i][0];
                num[i][0]=num[k][0];
                num[k][0]=tmp[0];
            }
        }
    }
    
    j=cnt;
    cnt=0;
    while(1)
    {        
        for(k=0;k<j;k++)
        {
            res[cnt++]=num[k][0];
            num[k][1]--;
        }
        if(num[0][1]==0) break;//cnt==tasksSize        
        for(k=0;k<n-j+1;k++)
        {
            res[cnt++]='a';
        }
        if(num[j-1][1]==0) j--;
    }
    return cnt;
}


int leastInterval2(char* tasks, int tasksSize, int n){
    int num[26]={0};
    int i,index;
    int max=0;
    int cnt=0;
    int len=0;
    
    if(n==0) return tasksSize;
    
    for(i=0;i<tasksSize;i++)
    {
        index = tasks[i]-'A';
        num[index]++;
        if(max<num[index])
        {
            max=num[index];
        }
    }
    for(i=0;i<26;i++)
    {
        if(max==num[i])
        {
            cnt++;
        }
    }
    if(cnt>n) return tasksSize;
    
    return (max-1)*(n+1)+cnt;
}


int leastInterval3(char* tasks, int tasksSize, int n){
    int num[26]={0};
    int i,index,k;
    int max=0;
    int cnt=0;
    int maxcnt=0;
    int len=0;
    
    if(n==0) return tasksSize;
    
    for(i=0;i<tasksSize;i++)
    {
        index = tasks[i]-'A';
        num[index]++;
        if(max<num[index])
        {
            max=num[index];
        }
    }
    
    k=max;
    do
    {
        cnt=0;
        for(i=0;i<26;i++)
        {
            if(k==num[i])
            {
                cnt++;
                if(k==max) maxcnt=cnt;
            }
        }
        if(cnt>n) return tasksSize;
    }while(--k>n);
    
    //printf("%d,%d,%d",max,maxcnt,len);
    return (max-1)*(n+1)+maxcnt;
}