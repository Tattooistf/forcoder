/*
 * @lc app=leetcode.cn id=732 lang=c
 *
 * [732] 我的日程安排表 III
 *
 * https://leetcode-cn.com/problems/my-calendar-iii/description/
 *
 * algorithms
 * Hard (58.90%)
 * Likes:    62
 * Dislikes: 0
 * Total Accepted:    3K
 * Total Submissions: 4.8K
 * Testcase Example:  '["MyCalendarThree","book","book","book","book","book","book"]\n' +
  '[[],[10,20],[50,60],[10,40],[5,15],[5,10],[25,55]]'
 *
 * 当 k 个日程安排有一些时间上的交叉时（例如 k 个日程安排都在同一时间内），就会产生 k 次预订。
 * 
 * 给你一些日程安排 [start, end) ，请你在每个日程安排添加后，返回一个整数 k ，表示所有先前日程安排会产生的最大 k 次预订。
 * 
 * 实现一个 MyCalendarThree 类来存放你的日程安排，你可以一直添加新的日程安排。
 * 
 * 
 * MyCalendarThree() 初始化对象。
 * int book(int start, int end) 返回一个整数 k ，表示日历中存在的 k 次预订的最大值。
 * 
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 输入：
 * ["MyCalendarThree", "book", "book", "book", "book", "book", "book"]
 * [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
 * 输出：
 * [null, 1, 1, 2, 3, 3, 3]
 * 
 * 解释：
 * MyCalendarThree myCalendarThree = new MyCalendarThree();
 * myCalendarThree.book(10, 20); // 返回 1 ，第一个日程安排可以预订并且不存在相交，所以最大 k 次预订是 1 次预订。
 * myCalendarThree.book(50, 60); // 返回 1 ，第二个日程安排可以预订并且不存在相交，所以最大 k 次预订是 1 次预订。
 * myCalendarThree.book(10, 40); // 返回 2 ，第三个日程安排 [10, 40) 与第一个日程安排相交，所以最大 k
 * 次预订是 2 次预订。
 * myCalendarThree.book(5, 15); // 返回 3 ，剩下的日程安排的最大 k 次预订是 3 次预订。
 * myCalendarThree.book(5, 10); // 返回 3
 * myCalendarThree.book(25, 55); // 返回 3
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 
 * 每个测试用例，调用 book 函数最多不超过 400次
 * 
 * 
 */

// @lc code=start



typedef struct {
    int count;
    int s[401];
    int e[401];
} MyCalendarThree;


MyCalendarThree* myCalendarThreeCreate() {
    MyCalendarThree *cal = (MyCalendarThree*)malloc(sizeof(MyCalendarThree));
    memset(cal,0,sizeof(MyCalendarThree));
    return cal;
}

int cmp(const void *a, const void *b)
{
    int *vala = (int *)a;
    int *valb = (int *)b;
    if (*vala < *valb)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void addCal(MyCalendarThree *obj, int start, int end)
{
    // obj->s[obj->count] = start;
    // obj->e[obj->count] = end;
    // obj->count++;

    // qsort(obj->s,obj->count,sizeof(int),cmp);
    // qsort(obj->e,obj->count,sizeof(int),cmp);

    // 下面的更高效
    if (obj->count == 0)
    {
        obj->s[0] = start;
        obj->e[0] = end;
        obj->count++;
        return;
    }
    
    int i = 0;
    for (i = obj->count-1; i >= 0; i--)
    {
        if (start < obj->s[i])
        {
            obj->s[i+1] = obj->s[i];
        }
        else
        {
            break;
        }
    }
    obj->s[i+1] = start;  // 前面漏掉了for循环都不满足的情况

    for (i = obj->count-1; i >= 0; i--)
    {
        if (end < obj->e[i])
        {
            obj->e[i+1] = obj->e[i];
        }
        else
        {
            break;
        }
    }
    obj->e[i+1] = end;

    obj->count++;
    return;
}
#define max(a,b) ((a)>(b)?(a):(b))
int myCalendarThreeBook(MyCalendarThree* obj, int start, int end) {
    addCal(obj, start, end);
    int count = 0;
    int total = obj->count;
    int i = 0;
    int j = 0;
    int maxcnt = 0;
    while(i<total && j<total)
    {
        // if (obj->s[i] == obj->e[j])
        // {
        //     j++;
        //     continue;
        // }
        
        if (obj->s[i] < obj->e[j])
        {
            count++;
            i++;
        }
        else
        {
            count--;
            j++;
        }
        maxcnt = max(count,maxcnt);
    }
    return maxcnt;
}

void myCalendarThreeFree(MyCalendarThree* obj) {
    if (obj != NULL)
    {
        free(obj);
        obj = NULL;
    }
    return;
}

/**
 * Your MyCalendarThree struct will be instantiated and called as such:
 * MyCalendarThree* obj = myCalendarThreeCreate();
 * int param_1 = myCalendarThreeBook(obj, start, end);
 
 * myCalendarThreeFree(obj);
*/
// @lc code=end

