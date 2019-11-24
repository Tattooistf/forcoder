#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"


int A0[]={1,2,3,4};
int A1[]={5,6,7,8};
int A2[]={9,10,11,12};
int *A[]={A0,A1,A2};
int B[]={4,4,4};
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize);

int main()
{
    int result = 0;
    int *ptr=NULL;
    ptr=spiralOrder(A, 3, B, &result);
    printf("%d \n",result);

    return 0;
} 


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    int row=0;
    int col=0;
    int *a=NULL;
    int cnt=0;
    int rowsize,colsize;
    int rowtmp=0;
    int coltmp=0;

    if(returnSize==NULL) return NULL;
    *returnSize=0;
    
    if((matrix==NULL)||(matrixColSize==NULL)||(matrixSize==0))
        return a;   
    a=(int *)malloc(sizeof(int) * matrixSize * *matrixColSize);
    if (a==NULL) {
        return NULL;
    }
    rowsize=matrixSize;
    colsize=*matrixColSize;

    while(row<=rowsize/2 || col<=colsize/2){

        if(row<=rowsize/2)
        {
            for(int i = col; i < colsize-col; i++)
            {
                a[cnt++]=matrix[row][i];
            }
            if (cnt>=(rowsize*colsize)) {
                break;
            }    
        }

        if(col<=colsize/2)
        {
            for(int i = row+1; i < rowsize-row-1; i++)
            {
                a[cnt++]=matrix[i][colsize-col-1];     
            }
            if (cnt>=(rowsize*colsize)) {
                break;
            }        
        }
        if(row<=rowsize/2)
        {
            for(int i = colsize-col-1; i >=col; i--)
            {
                a[cnt++]=matrix[rowsize-row-1][i];    
            }    
            if (cnt>=(rowsize*colsize)) {
                break;
            }        
            rowtmp++;  
        }  
        if(col<=colsize/2)
        {    
            for(int i = rowsize-row-2; i >row; i--)
            {
                a[cnt++]=matrix[i][col];      
            }   
            if (cnt>=(rowsize*colsize)) {
                break;
            }        
            coltmp++;
        } 
        row=rowtmp;
        col=coltmp;

    }

    for(int i = 0; i < colsize*rowsize; i++)
    {
        printf("%d",a[i]);
    }
    printf("\n");
    *returnSize=cnt;

    return a;
        
}





