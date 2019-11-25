#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "ctype.h"

int evalRPN(char ** tokens,int tokensSize);
char *A[]={"10","6","9","3","+","-11","*","/","*","17","+","5","+"};

int main()
{
    int a=0;
    a=evalRPN(A,sizeof(A)/sizeof(A[0]));
    printf("result is %d\n",a);
    system("pause");
    return 0;
}

bool isNumber(char *str)
{
    if (*str=='-' && *(str+1)!='\0')
    {
        str++;
    }

    if (*str<'0' || *str>'9')
    {
        return false;
    }
    return true;
}

int stack[10000]={0};//栈的实现方式有点投机，用例刚好10000能过，实际上需要动态申请和释放才行
int ptr=0;

void pushstack(int num)
{
    stack[ptr++]=num;
    return;
}

int popstack()
{
    return stack[--ptr];
}

int covert(char *str)
{
    int sum=0;
    int flag=1;
    if (*str=='-')
    {
        str++;
        flag=-1;
    }
    
    while (*str)
    {
        sum=sum*10+(*str++-'0');
    }
    return sum*flag;
}

int evalRPN(char ** tokens,int tokensSize){
    int a,b;
    int count=0;

    for (int i = 0; i < tokensSize; i++)
    {
        if (isNumber(tokens[i]))//通过反向判断比较合适，判断是否为操作符，非操作符就表示是数据
        {
            pushstack(covert(tokens[i]));//转化函数实际上就是atoi
            continue;
        }
        b=popstack();
        a=popstack();
        switch (*(tokens[i]))
        {
            case '*':
                count=a*b;
                pushstack(count);
                break;
            case '/':
                count=a/b;
                pushstack(count);
                break;
            case '+':
                count=a+b;
                pushstack(count);
                break;
            case '-':
                count=a-b;
                pushstack(count);
                break;
                                                
            default:
                break;
        }
        
    }

    return popstack();
    
}