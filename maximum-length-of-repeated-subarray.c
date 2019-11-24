#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int A[]={1,2,3,2,1};
int B[]={3,2,1,4,7};

int findLength(int* A, int ASize, int* B, int BSize);

int main()
{
    int result=0;
    result=findLength(A, sizeof(A)/sizeof(A[0]),B,sizeof(B)/sizeof(B[0]));
    printf("%d\n",result);
    return 0;
}  

//1.暴力破解法2.通过max提升进度
//1maximum-length-of-repeated-subarray
int findLength(int* A, int ASize, int* B, int BSize){
    int i,j;
    int len=1;
    int max=0;

    for( i = 0; i+max < ASize; i++)
    {
        for( j = 0; j+max < BSize; j++)
        {
            if (A[i]!=B[j]) {
                continue;
            }
            len=1;
            
            while((i+len<ASize)&&(j+len<BSize)&&(A[i+len]==B[j+len])) {
                len++;
            }
            max=max>len?max:len;
        }
        
    }
    
    return max;
}


