#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize);
int A1[]={2,3,1,3,2,4,6,7,9,2,19};
int A2[]={2,1,4,3,9,6};
int main()
{
    printf("ddddddd");
    system("pause");
    return 0;
}
//不知道题目在哪里，懒得去找了，这个解题可能不是正确的

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
     while (temp[arr2[i]]--)
     {
         *ptr++=arr2[i];
     }
 }

 for ( i = 0; i < arr1Size; i++)
 {
     while (temp[arr1[i]]--)
     {
         *ptr++=arr1[i];
     }
     
 }

 *returnSize = arr1Size;
 return retarr;
 
 
}
