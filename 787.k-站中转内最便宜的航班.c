/*
 * @lc app=leetcode.cn id=787 lang=c
 *
 * [787] K 站中转内最便宜的航班
 *
 * https://leetcode-cn.com/problems/cheapest-flights-within-k-stops/description/
 *
 * algorithms
 * Medium (36.11%)
 * Likes:    188
 * Dislikes: 0
 * Total Accepted:    10.6K
 * Total Submissions: 29K
 * Testcase Example:  '3\n[[0,1,100],[1,2,100],[0,2,500]]\n0\n2\n1'
 *
 * 有 n 个城市通过 m 个航班连接。每个航班都从城市 u 开始，以价格 w 抵达 v。
 * 
 * 现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到从 src 到 dst 最多经过 k 站中转的最便宜的价格。
 * 如果没有这样的路线，则输出 -1。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入: 
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 1
 * 输出: 200
 * 解释: 
 * 城市航班图如下
 * 
 * 
 * 从城市 0 到城市 2 在 1 站中转以内的最便宜价格是 200，如图中红色所示。
 * 
 * 示例 2：
 * 
 * 
 * 输入: 
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 0
 * 输出: 500
 * 解释: 
 * 城市航班图如下
 * 
 * 
 * 从城市 0 到城市 2 在 0 站中转以内的最便宜价格是 500，如图中蓝色所示。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n 范围是 [1, 100]，城市标签从 0 到 n - 1
 * 航班数量范围是 [0, n * (n - 1) / 2]
 * 每个航班的格式 (src, dst, price)
 * 每个航班的价格范围是 [1, 10000]
 * k 范围是 [0, n - 1]
 * 航班没有重复，且不存在自环
 * 
 * 
 */

// @lc code=start


// 尝试使用出入度的方式解决，类似BFS队列方式
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX 10000
int Q[MAX] = {0};
int g_Wr = 0;
int g_Rd = 0;
int g_Count = 0;
void QueueInit(void)
{
    g_Wr = 0;
    g_Rd = 0;
    g_Count = 0;
    memset(Q,0,sizeof(Q));
    return;
}

void enQueue(int index)
{
    if (g_Count == MAX)
    {
        printf("FULL\n");
        return;
    }
    Q[g_Wr] = index;
    g_Wr =  (g_Wr+1)%MAX;
    g_Count++; // 差一点忘记计数刷新
    return;
}

int deQueue(void)
{
    if (g_Count == 0)
    {
        printf("EMPTY\n");
        return -1;
    }
    int val = Q[g_Rd];
    g_Rd = (g_Rd+1)%MAX;
    g_Count--;
    return val;    
}

int isEmpty(void)
{
    return (g_Count == 0);
}
int QueueCnt(void)
{
    return g_Count;
}

#define min(a,b) ((a)<(b)?(a):(b))
// BFS超时39/47，设置的不好内部两层for循环
int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int K){
    int res = 0;
    int array[100][100] = {0};
    int sum[100][100] = {0};
    //int **sum = (int **)malloc(n*K*sizeof(int)); // 每个航班K步可到的最小价格
    //memset(sum,0,n*K*sizeof(int));

    QueueInit();

    for (int i = 0; i < flightsSize; i++)
    {
        array[flights[i][0]][flights[i][1]]=flights[i][2];
        if (flights[i][0] == src)
        {
            enQueue(flights[i][1]);//带节点号和价格两个信息，后面无法得知源头的问题就能解决
        }
    }

    int level = 0;
    while (!isEmpty() && level<=K)
    {
        int cnt = QueueCnt();
        for (int i = 0; i < cnt; i++)
        {
            int num = deQueue();
            int cur = (level == 0)?array[src][num]:(sum[src][level-1] + array[src][num]);
            sum[num][level] = (sum[num][level] == 0)?cur:min(sum[num][level],cur);

            if (num == dst)
            {
                continue;
            }
            for (int i = 0; i < n; i++)
            {
                if (array[num][i] != 0)
                {
                    enQueue(i);
                }
            }           
        }
        level++; 
    }
    unsigned int minPrice = 0xFFFFFFFF;
    for (int i = 0; i <= K; i++)
    {
        if(sum[dst][i] == 0) continue;
        minPrice = min(minPrice,sum[dst][i]);
    }
    return minPrice;
}
// @lc code=end

int main(void)
{
    int A[] = {0,1,100};
    int B[] = {1,2,100};
    int C[] = {0,2,500};
    int *array[] = {A,B,C};
    int Col[] = {3,3,3};
    int Price = findCheapestPrice(3,array,3,Col,0,2,1);
    return 0;
}

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int K){
    int res = 0;
    int sum[100][100] = {0};
    //int **sum = (int **)malloc(n*K*sizeof(int)); // 每个航班K步可到的最小价格
    //memset(sum,0,n*K*sizeof(int));

    QueueInit();

    for (int i = 0; i < flightsSize; i++)
    {
        if (flights[i][0] == src)
        {
            enQueue(i);
        }
    }

    int level = 0;
    while (!isEmpty() && level<=K)
    {
        int cnt = QueueCnt();
        for (int i = 0; i < cnt; i++)
        {
            int num = deQueue();
            int cur = (level == 0)?flights[num][2]:(sum[flights[num][0]][level-1] + flights[num][2]);
            sum[flights[num][1]][level] = (sum[flights[num][1]][level] == 0)?cur:min(sum[flights[num][1]][level],cur);

            if (flights[num][1] == dst)
            {
                continue;
            }
            for (int i = 0; i < flightsSize; i++)
            {
                if (flights[i][0] == flights[num][1])
                {
                    enQueue(i);
                }
            }           
        }
        level++; 
    }
    unsigned int minPrice = 0xFFFFFFFF;
    for (int i = 0; i <= K; i++)
    {
        if(sum[dst][i] == 0) continue;
        minPrice = min(minPrice,sum[dst][i]);
    }
    return minPrice;
}