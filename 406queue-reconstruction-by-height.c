#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int A0[]={7,0};
int A1[]={4,4};
int A2[]={7,1};
int A3[]={5,0};
int A4[]={6,1};
int A5[]={5,2};
int *A[]={A0,A1,A2,A3,A4,A5};
int B[]={2,2,2,2,2,2};

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes);

int main()
{
    int **result=0;
    int resSize = 0;
    int *colSizes=0;
    result=reconstructQueue(A,sizeof(A)/sizeof(A[0]),B,&resSize,&colSizes);

    printf("[");
    for(int i = 0; i < resSize; i++)
    {
        printf("[");
        for(int j = 0; j < colSizes[i]; j++)
        {
            printf("%d",result[i][j]);
            if (j<colSizes[i]-1) {
                printf(",");
            }
            
        }
        printf("]");
        if (i<resSize-1) {
            printf(",");
        }
        
    }
    printf("]");
    printf("\n");

    return 0;
}  
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes){
    int **queue=0;
    int *colsize=0;
    int *tmp;
    int tmpsize;
    int flag[1100]={0};
    int i,j;
    int cnt=0;

    queue=(int **)malloc(sizeof(int *)*peopleSize);
    colsize=(int *)malloc(sizeof(int)*peopleSize);

    //先按照身高从小到大排序，处理最小身高的位置（因为是最小，所以下标是多少就表示位置是多少）
    for(i = 0; i < peopleSize; i++)
    {
        for(j = i+1; j < peopleSize; j++)
        {
            if(people[i][0]>people[j][0])
            {
                tmp=people[i];
                people[i]=people[j];
                people[j]=tmp;

                tmpsize=peopleColSize[i];
                peopleColSize[i]=peopleColSize[j];
                peopleColSize[j]=tmpsize;
            }
        }
        
    }

    for(i = 0; i < peopleSize; i++)
    {
        int *array=(int *)malloc(sizeof(people[i]));
        array[0]=people[i][0];
        array[1]=people[i][1];
        cnt=0;
        for( j = 0; j < peopleSize; j++)
        {
            if (flag[j]!=0) {
                if(array[0]==queue[j][0]) cnt++;
                continue;
            }
            cnt++;
            if (cnt==array[1]+1) {
                queue[j]=array;
                flag[j]=1;
                colsize[j]=2;
            }
        }
        
    }
    *returnSize=peopleSize;
    *returnColumnSizes=colsize;

    return queue;
}


