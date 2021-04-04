/*
 * @lc app=leetcode.cn id=857 lang=c
 *
 * [857] 雇佣 K 名工人的最低成本
 *
 * https://leetcode-cn.com/problems/minimum-cost-to-hire-k-workers/description/
 *
 * algorithms
 * Hard (46.83%)
 * Likes:    107
 * Dislikes: 0
 * Total Accepted:    2.3K
 * Total Submissions: 4.9K
 * Testcase Example:  '[10,20,5]\n[70,50,30]\n2'
 *
 * 有 N 名工人。 第 i 名工人的工作质量为 quality[i] ，其最低期望工资为 wage[i] 。
 * 
 * 现在我们想雇佣 K 名工人组成一个工资组。在雇佣 一组 K 名工人时，我们必须按照下述规则向他们支付工资：
 * 
 * 
 * 对工资组中的每名工人，应当按其工作质量与同组其他工人的工作质量的比例来支付工资。
 * 工资组中的每名工人至少应当得到他们的最低期望工资。
 * 
 * 
 * 返回组成一个满足上述条件的工资组至少需要多少钱。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入： quality = [10,20,5], wage = [70,50,30], K = 2
 * 输出： 105.00000
 * 解释： 我们向 0 号工人支付 70，向 2 号工人支付 35。
 * 
 * 示例 2：
 * 
 * 输入： quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
 * 输出： 30.66667
 * 解释： 我们向 0 号工人支付 4，向 2 号和 3 号分别支付 13.33333。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= K <= N <= 10000，其中 N = quality.length = wage.length
 * 1 <= quality[i] <= 10000
 * 1 <= wage[i] <= 10000
 * 与正确答案误差在 10^-5 之内的答案将被视为正确的。
 * 
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

// @lc code=start
typedef struct ratio
{
    int idx;
    double val;
}ratio;

double Min(double a, double b)
{
    return a>b?b:a;
}

int cmp(const void *a, const void *b)
{
    ratio *tmpa = (ratio *)a;
    ratio *tmpb = (ratio *)b;
    if (tmpa->val < tmpb->val)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int *g_Heap = NULL;
int g_Size = 0;
void HeapInit(int size)
{
    g_Heap = (int *)malloc(sizeof(int)*(size+1));
    memset(g_Heap,0,sizeof(int)*(size+1));
    g_Size = 0;
    return;
}

void HeapDestroy(void)
{
    if (g_Heap != NULL)
    {
        free(g_Heap);
    }
    g_Heap = NULL;
    g_Size = 0;
    return;    
}

void HeapPush(int value)
{
    g_Heap[++g_Size] = value; //再次栽坑，heap从1开始
    int i = 0;
    for (i = g_Size; (i>>1) > 0; i=i>>1)
    {
        if (g_Heap[i>>1] < value)
        {
            g_Heap[i] = g_Heap[i>>1];
        }
        else
        {
            break;
        }
    }
    g_Heap[i] = value;

    return;
}

int HeapPop(void)
{
    int ret = g_Heap[1];
    int value = g_Heap[g_Size];
    g_Size--;
    int j = 0;
    int i = 0;
    for (i = 1; 2*i <= g_Size; i=j)
    {
        if ((2*i+1) <= g_Size && g_Heap[2*i+1] > g_Heap[2*i])
        {
            j = 2*i+1;
        }
        else
        {
            j = 2*i;
        }
        
        if (g_Heap[j] > value)
        {
            g_Heap[i] = g_Heap[j];
        }
        else
        {
            break;
        }
    }
    g_Heap[i] = value;

    return ret;
}

// 使用堆求解，也就是优先级队列
double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int wageSize, int K){
    ratio *rat = (double *)malloc(sizeof(ratio)*wageSize);
    memset(rat,0,sizeof(ratio)*wageSize);
    for (int i = 0; i < wageSize; i++)
    {
        rat[i].val = wage[i]/(quality[i]*1.0);
        rat[i].idx = i;
    }
    qsort(rat,wageSize,sizeof(ratio),cmp);
    
    double sum = 0;
    double ret = 1000000000;
    HeapInit(wageSize);
    for (int i = 0; i < wageSize; i++)
    {
        int index = rat[i].idx;  
        double val = rat[i].val;      
        if (i < K)
        {
            HeapPush(quality[index]);
            sum+=quality[index];
            if (i == K-1)
            {
                ret = sum*val;
            } 
        }
        else
        {
            HeapPush(quality[index]);
            double tmp = HeapPop();
            sum += quality[index]-tmp; //出现过疏忽，出入的计算弄反了
            ret = Min(ret,sum*val);            
        }
    }
    HeapDestroy();
    free(rat);
    return ret;
}


// @lc code=end

int main()
{
    int quality[] = {10,20,5};    
    int wage[] = {70,50,30};

    double ret = mincostToHireWorkers(quality,sizeof(quality)/sizeof(quality[0]),wage,sizeof(wage)/sizeof(wage[0]),2);
    return 0;
}

/*
// 第一次下手的思路，完全不正确；存在两方面的问题，对工作质量比例理解不准确，对算法没想到（贪心或堆）
double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int wageSize, int K){
    int *wageIndex = (int *)malloc(sizeof(int)*wageSize);
    int *qualityIndex = (int *)malloc(sizeof(int)*wageSize);
    for (int i = 0; i < wageSize; i++)
    {
        wageIndex[i] = i;
        qualityIndex[i] = i;
    }
    
    for (int i = 0; i < wageSize; i++)
    {
        for (int j = i+1; j < wageSize; j++)
        {
            if (wage[i] > wage[j])
            {
                int index = wageIndex[i];
                wageIndex[i] = wageIndex[j];
                wageIndex[j] = index;
            }

            if (quality[i] > quality[j])
            {
                int index = qualityIndex[i];
                qualityIndex[i] = qualityIndex[j];
                qualityIndex[j] = index;
            }            
        }
    }

    double min = 0;
    double ret = 0;
    for (int i = 0; i < K; i++)
    {
        int index = wageIndex[i];
        for (int j = 0; j < wageSize; j++)
        {
            if (index == j)
            {
                continue;
            }
            
            double tmp = 0;
            if(quality[j]/quality[index]*wage[index] >= wage[j])
            {
                tmp = quality[j]/quality[index]*wage[index];
            }
            else
            {
                tmp = quality[index]/quality[j]*wage[j];
            }
            min = Min(min,tmp);
        }
        ret += min;

    }
    
    return ret;
}

//第二次看过答案后采用贪心法求解，会出现超时

double Min(double a, double b)
{
    return a>b?b:a;
}

int cmp(const void *a, const void *b)
{
    int *tmpa = (int *)a;
    int *tmpb = (int *)b;
    if (*tmpa<*tmpb)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// 先按照贪心法解题
double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int wageSize, int K){
    int *qualitytmp = (int *)malloc(sizeof(int)*wageSize);
    memset(qualitytmp,0,sizeof(int)*wageSize);
    double ret = 100000000;
    for (int i = 0; i < wageSize; i++)
    {
        int idx = 0;
        double ratio = wage[i]/(quality[i]*1.0); //一个低级错误，整型相除没有小数点，需要转换为浮点
        for (int j = 0; j < wageSize; j++)
        {   
            double value = ratio * quality[j];
            if (value >= wage[j])
            {
                qualitytmp[idx++] = quality[j];
            }
        }
        if (idx < K)
        {
            continue;
        }
        qsort(qualitytmp,idx, sizeof(int),cmp);
        double sum = 0;
        for (int i = 0; i < K; i++)
        {
            sum+=qualitytmp[i];
            //printf("%d\n",qualitytmp[i]);
        }
        ret = Min(ret,sum*ratio);
    }
    free(qualitytmp);
    return ret;
}

*/