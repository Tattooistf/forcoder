#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/*
 * i have a very simple problem for you.
 * Given two integers A and B,you job is to multiply the product is of A*B
 */
void cal(int *a,int *b,int asize,int bsize);

#define MAXLEN 1000
int a[MAXLEN]={0};
int b[MAXLEN]={0};
int result[2*MAXLEN]={0};
int main(void)
{
    int asize=0;
    int bsize=0;

    /*输入解决顺序颠倒的问题，直接输入的时候反转出来*/
    char *ptmp=(char *)malloc(sizeof(char)*MAXLEN);
    scanf("%s",ptmp);

    asize=strlen(ptmp);
    for (int i = 0; i < asize; i++)
    {
        a[asize-i-1]=ptmp[i]-'0';
    }
    scanf("%s",ptmp);
    bsize=strlen(ptmp);
    for (int i = 0; i < bsize; i++)
    {
        b[bsize-i-1]=ptmp[i]-'0';
    }

    cal(a,b,asize,bsize);
    int flag=0;
    for (int i = 0; i < asize+bsize; i++)
    {
        if (flag==0 && result[asize+bsize-i-1]==0)
        {
            continue;
        }
        if (result[asize+bsize-i-1]!=0)
        {
            flag=1;
        }
        printf("%d",result[asize+bsize-i-1]);
    }
    return 0;
}

/* each line will contain two integers A and B.Process to end of file.Notice that the integers are bery large,that means hou should
not process them by using 32bit integer.You may assume the length od each integer will not exceed 1000

For each case ,output the product is of A*B in one line */
void cal(int *a,int *b,int asize,int bsize)
{
    int tmp = 0;
    for (int i = 0; i < asize; i++)
    {
        for (int j = 0; j < bsize; j++)
        {
            result[i+j]+=a[i]*b[j];//第一次没有搞清楚，没有使用+=操作符
            //关键的也是上面的等式你能想到准
        }
    }

    int carry=0;
    for (int i = 0; i < asize+bsize; i++)
    {
        tmp=result[i]+carry;
        carry=tmp/10;
        result[i]=tmp%10;
    }
    return;
}

