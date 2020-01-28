#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/* 最刚开始对于溢出情况没想明白，后面增加正数的判断，但漏了对于负数的处理；
 * 上面的条件都增加后还是有问题，是对整数判断条件的转换没搞清楚；0x80000000是作为无符号整数来处理的；增加
 * 强转后问题解决；
 * 第一次提交性能交差，将判断条件放到循环外面后性能提升明显；
 */
int main(void)
{
    int value=0;
    int retValue = 0;
    scanf("%d",&value);
    printf("%d\n",value);
    retValue = reverse(value);
    printf("%d\n",retValue);
    return 0;
}
// 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
// 假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−231,  231 − 1]。请根据这个假设，如果反转后整数溢出那么就返回 0。
int reverse(int x){
    int value = x;
    long result = 0;/* 此处long long修改成long能节省内存，但不一定是最合理的。部分机器下long和int可能是同样的位宽 */

    while (value)
    {
        result = result*10+value%10;        
        value=value/10;
    }
    if (result>(int)0x7fffffff || result < (int)0x80000000)
    {
        return 0;
    }    
    return result;
}

