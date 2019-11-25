#include "stdio.h"
#include "string.h"
#include "memory.h"
#include "stdlib.h"

int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize);
int A1[]={2,3,1,3,2,4,6,7,9,2,19};
int A2[]={2,1,4,3,9,6};
int main()
{
    int retSize=0;
    int *ptr=NULL;
    ptr=relativeSortArray(A1,sizeof(A1)/sizeof(A1[0]),A2,sizeof(A2)/sizeof(A2[0]),&retSize);
    for (int i = 0; i < retSize; i++)
    {
        printf("%d,",*(ptr+i));
    }
    
    return 0;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize){
 int *retarr=(int *)malloc(sizeof(int)*arr1Size);
 int *ptr=NULL;
 int temp[1000]={0};
 int i=0;
//计算出所有元素出现的次数
 for (i = 0; i < arr1Size; i++)
 {
     temp[arr1[i]]++;
 }

ptr=retarr;
 for ( i = 0; i < arr2Size; i++)
 {
     while (temp[arr2[i]])
     {
         *ptr++=arr2[i];
		 temp[arr2[i]]--;
     }
 }

 for ( i = 0; i < arr1Size; i++)
 {
     while (temp[arr1[i]])
     {
         *ptr++=arr1[i];
		 temp[arr1[i]]--;
     }
     
 }

 *returnSize = arr1Size;
 return retarr;
 
 
}
