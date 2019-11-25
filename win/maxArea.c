#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int maxArea(int* height, int heightSize);
int A[]={1,8,6,62,5,4,8,3,7};

int main()
{
    int a=0;
    a=maxArea(A,sizeof(A)/sizeof(A[0]));
    printf("result is %d\n",a);
    system("pause");
    return 0;
}

#define min(a,b) ((a)>(b)?(b):(a))

int maxArea(int* height, int heightSize){
    int left,right,max;
    int area=0;

    max = 0;
    left = 0;
    right = heightSize-1;
    max = min(height[right],height[left])*(right-left);
    while (left<right)
    {
        //如果left>right则选定left，然后再找比right更大的right；如果找到且面积比之前的大，则固定righ
        //再继续寻找比right大的left，循环进行
        while ((height[left]<=height[right])&&(left<right))
        {
            area=height[left]*(right-left);
            max=area>max?area:max;
            left++;
        }

        while ((height[right]<=height[left])&&(left<right))
        {
            area=height[right]*(right-left);
            max=area>max?area:max;
            right--;
        }       
    }
    return max;
}


//参考大牛的做法优化
int maxArea0(int* height, int heightSize){
    int left,right,max;
    int area=0;

    max = 0;
    left = 0;
    right = heightSize-1;
    
    while (left<right)
    {
        //如果left>right则选定left，然后再找比right更大的right；如果找到且面积比之前的大，则固定righ
        //再继续寻找比right大的left，循环进行
        area = min(height[right],height[left])*(right-left);
        max=area>max?area:max;
        if (height[left]<=height[right])
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    return max;
}