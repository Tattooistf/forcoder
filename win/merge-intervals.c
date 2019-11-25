#include "stdio.h"
#include "string.h"

int main()
{
	return 0;	
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int **ptr=(int **)malloc(intervalsSize*sizeof(int *));
    int *pCol=(int *)malloc(intervalsSize*sizeof(int));
    int num=0;
	int i=0;
	int j=0;
	if (intervalsSize ==0)
	{
        *returnSize=0;
		return NULL;
	}
    memset(ptr,0,intervalsSize*sizeof(int *));
    *returnColumnSizes = pCol;

    //首先进行排序
    for (i = 0; i < intervalsSize; i++)
    {
        for (j = i+1; j < intervalsSize; j++)
        {
            if (intervals[i][0]>intervals[j][0])
            {
                int *tmp=intervals[i];
                intervals[i]=intervals[j];
                intervals[j]=tmp;
            }
        }
    }
    
    //在进行区间合并
	int *tojuge=intervals[0];
	(*returnColumnSizes)[0]=intervalsColSize[0];
	ptr[num++]=tojuge;
    for (i = 1; i < intervalsSize; i++)
    {
		if (tojuge[1] >= intervals[i][0])
		{
			tojuge[1]=tojuge[1]>intervals[i][1]?tojuge[1]:intervals[i][1];
			intervals[i]=NULL;
		}
		else
		{
			tojuge = intervals[i];
			(*returnColumnSizes)[num]=intervalsColSize[i];
			ptr[num++]=tojuge;
		}
		
    }
    
    *returnSize = num;
    return ptr;
}
