/*
 * @lc app=leetcode.cn id=901 lang=c
 *
 * [901] 股票价格跨度
 *
 * https://leetcode-cn.com/problems/online-stock-span/description/
 *
 * algorithms
 * Medium (51.56%)
 * Likes:    134
 * Dislikes: 0
 * Total Accepted:    17.4K
 * Total Submissions: 32.2K
 * Testcase Example:  '["StockSpanner","next","next","next","next","next","next","next"]\n' +
  '[[],[100],[80],[60],[70],[60],[75],[85]]'
 *
 * 编写一个 StockSpanner 类，它收集某些股票的每日报价，并返回该股票当日价格的跨度。
 * 
 * 今天股票价格的跨度被定义为股票价格小于或等于今天价格的最大连续日数（从今天开始往回数，包括今天）。
 * 
 * 例如，如果未来7天股票的价格是 [100, 80, 60, 70, 60, 75, 85]，那么股票跨度将是 [1, 1, 1, 2, 1, 4,
 * 6]。
 * 
 * 
 * 
 * 示例：
 * 
 * 输入：["StockSpanner","next","next","next","next","next","next","next"],
 * [[],[100],[80],[60],[70],[60],[75],[85]]
 * 输出：[null,1,1,1,2,1,4,6]
 * 解释：
 * 首先，初始化 S = StockSpanner()，然后：
 * S.next(100) 被调用并返回 1，
 * S.next(80) 被调用并返回 1，
 * S.next(60) 被调用并返回 1，
 * S.next(70) 被调用并返回 2，
 * S.next(60) 被调用并返回 1，
 * S.next(75) 被调用并返回 4，
 * S.next(85) 被调用并返回 6。
 * 
 * 注意 (例如) S.next(75) 返回 4，因为截至今天的最后 4 个价格
 * (包括今天的价格 75) 小于或等于今天的价格。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 调用 StockSpanner.next(int price) 时，将有 1 <= price <= 10^5。
 * 每个测试用例最多可以调用  10000 次 StockSpanner.next。
 * 在所有测试用例中，最多调用 150000 次 StockSpanner.next。
 * 此问题的总时间限制减少了 50%。
 * 
 * 
 */

// @lc code=start



typedef struct {
    int *stack;
    int top;
    int *nums;
    int total;
} StockSpanner;

#define MAXNUM 10000
StockSpanner* stockSpannerCreate() {
    StockSpanner *obj = (StockSpanner *)malloc(sizeof(StockSpanner));
    obj->total = 0;
    obj->top = 0;
    obj->stack = (int *)malloc(sizeof(int)*MAXNUM);
    memset(obj->stack,0,sizeof(int)*MAXNUM);
    obj->nums = (int *)malloc(sizeof(int)*MAXNUM);
    memset(obj->nums,0,sizeof(int)*MAXNUM);
    return obj;
}

void StackPush(StockSpanner* obj, int val)
{
    if (obj->top == MAXNUM)
    {
        return;
    }
    obj->stack[obj->top++] = val;
    
    return;
}

int StackPop(StockSpanner* obj)
{
    if (obj->top == 0)
    {
        return 0xFFFFFFFF;
    }
    int ret = obj->stack[--obj->top];
    return ret;
}
int StackEmpty(StockSpanner* obj)
{
    return obj->top == 0;
}

int StackTop(StockSpanner* obj)
{
    return obj->stack[obj->top-1];
}

int stockSpannerNext(StockSpanner* obj, int price) {
    obj->nums[obj->total] = price;

    int ret = 0;
    // int index = obj->total;
    while (!StackEmpty(obj) && obj->nums[StackTop(obj)] <= price)
    {
        // index = StackPop(obj);
        StackPop(obj);
    }

    if (!StackEmpty(obj))
    {
        ret = obj->total - StackTop(obj);
    }
    else
    {
        ret = obj->total+1; // 错误：obj->total-index+1；实际上为空的时候直接就是total的值
    }

    StackPush(obj,obj->total);
    obj->total++;
    return ret;
}

void stockSpannerFree(StockSpanner* obj) {
    if (obj)
    {
        obj->total = 0;
        obj->top = 0;
        if (obj->stack)
        {
            free(obj->stack);
            obj->stack = NULL;
        }
        if (obj->nums)
        {
            free(obj->nums);
            obj->nums = NULL;
        }
        free(obj);
    }
    obj = NULL;
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);
 
 * stockSpannerFree(obj);
*/
// @lc code=end

