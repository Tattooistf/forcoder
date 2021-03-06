#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

//调试通过，C语言中性能很好，可是内存使用只有57%，估计是使用strtok比较多的原因

char str[40];//按照IPv6最大长度来申请
#define IPV4 "IPv4"
#define IPV6 "IPv6"
#define NOR "Neither"
char * validIPAddress(char * IP);

int main(void)
{
    char *ret=NULL;
    scanf("%s",str);
    ret=validIPAddress(str);

    printf("%s\n",ret);
    return 0;
}
int IsIpv4(char *p)
{
    if ((strlen(p)>1 && *p=='0') || strlen(p)>3)
    {
        return 0;
    }    

    char *ptmp=p;
    while (*ptmp!='\0')
    {
        if(*ptmp<'0' || *ptmp>'9') return 0;
        ptmp++;
    }
    
    int value=atoi(p);
    if (value < 0 || value > 255)
    {
        return 0;
    }
    
    return 1;
}

int IsIpv6(char *p)
{
    if (strlen(p)>4)
    {
        return 0;
    }

    char *ptmp=p;
    while (*ptmp!='\0')
    {
        if((*ptmp>='0' && *ptmp<='9')
        ||(*ptmp>='a' && *ptmp<='f')
        ||(*ptmp>='A' && *ptmp<='F'))
        {
            ptmp++;
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

char * validIPAddress(char * IP){
    char *ptr=NULL;
    char *str=IP;
    int count4=0;
    int count6=0;
    int count=0;

    //判断是否为IPv4和IPv6分隔符个数
    while (*str!='\0')
    {
        if (*str=='.')
        {
            count4++;
        }
        if (*str==':')
        {
            count6++;
        }
        str++; 
    }
    if (count4 != 3 && count6 != 7)
    {
        return NOR;
    }
    
    if (count4 == 3)
    {
        //判断是否为IPv4
        ptr=strtok(IP,".");
        while (ptr!=NULL)
        {
            count++;
            if(!IsIpv4(ptr)) return NOR;
            ptr=strtok(NULL,".");
        }    
        if (count!=count4+1)
        {
            return NOR;
        }
            
        return IPV4;
    }
    else
    {
        //判断是否为IPv6
        ptr=strtok(IP,":");
        while (ptr!=NULL)
        {
            count++;
            if(!IsIpv6(ptr)) return NOR;
            ptr=strtok(NULL,":");
        }   
        if (count!=count6+1)
        {
            return NOR;
        }                   
        return IPV6;
    }
}

//对代码进行优化，减少重复率；但是因为使用了函数指针从而导致性能上增加了4ms，整体表现不如上一个题解
char * validIPAddress2(char * IP){
    char *str=IP;
    int count4=0;
    int count6=0;
    int count=0;
    int countbase=0;
    char *ret=NULL;

    //判断是否为IPv4和IPv6分隔符个数
    while (*str!='\0')
    {
        if (*str=='.')
        {
            count4++;
        }
        if (*str==':')
        {
            count6++;
        }
        str++; 
    }
    if (count4 != 3 && count6 != 7)
    {
        return NOR;
    }

    char *splitstr=NULL;
    typedef int (*pfFunc)(char *);
    pfFunc pfcheckfunc=NULL;
    if (count4 == 3) //表示为IPv4，否则为IPv6
    {
        splitstr=".";
        pfcheckfunc=IsIpv4;
        countbase=count4+1;
        ret=IPV4;
    }
    else
    {
        splitstr=":";
        pfcheckfunc=IsIpv6;
        countbase=count6+1;
        ret=IPV6;
    }

    //判断是否满足要求
    str=strtok(IP,splitstr);
    while (str!=NULL)
    {
        count++;
        if(!pfcheckfunc(str)) return NOR;
        str=strtok(NULL,splitstr);
    }    
    if (count!=countbase)
    {
        return NOR;
    }   
    return ret;      
}

