/*
 * @lc app=leetcode.cn id=729 lang=c
 *
 * [729] 我的日程安排表 I
 *
 * https://leetcode-cn.com/problems/my-calendar-i/description/
 *
 * algorithms
 * Medium (49.96%)
 * Likes:    85
 * Dislikes: 0
 * Total Accepted:    6.9K
 * Total Submissions: 13.6K
 * Testcase Example:  '["MyCalendar","book","book","book"]\n[[],[10,20],[15,25],[20,30]]'
 *
 * 实现一个 MyCalendar 类来存放你的日程安排。如果要添加的时间内没有其他安排，则可以存储这个新的日程安排。
 * 
 * MyCalendar 有一个 book(int start, int end)方法。它意味着在 start 到 end
 * 时间内增加一个日程安排，注意，这里的时间是半开区间，即 [start, end), 实数 x 的范围为，  start 。
 * 
 * 当两个日程安排有一些时间上的交叉时（例如两个日程安排都在同一时间内），就会产生重复预订。
 * 
 * 每次调用 MyCalendar.book方法时，如果可以将日程安排成功添加到日历中而不会导致重复预订，返回 true。否则，返回 false
 * 并且不要将该日程安排添加到日历中。
 * 
 * 请按照以下步骤调用 MyCalendar 类: MyCalendar cal = new MyCalendar();
 * MyCalendar.book(start, end)
 * 
 * 示例 1:
 * 
 * 
 * MyCalendar();
 * MyCalendar.book(10, 20); // returns true
 * MyCalendar.book(15, 25); // returns false
 * MyCalendar.book(20, 30); // returns true
 * 解释: 
 * 第一个日程安排可以添加到日历中.  第二个日程安排不能添加到日历中，因为时间 15 已经被第一个日程安排预定了。
 * 第三个日程安排可以添加到日历中，因为第一个日程安排并不包含时间 20 。
 * 
 * 
 * 说明:
 * 
 * 
 * 每个测试用例，调用 MyCalendar.book 函数最多不超过 1000次。
 * 调用函数 MyCalendar.book(start, end)时， start 和 end 的取值范围为 [0, 10^9]。
 * 
 * 
 */

// @lc code=start

// 区间：存放的日历按照end从小到大排序，新插入的也必须遵循这一规则
// 比较幸运，一次编写调试通过

typedef struct {
    int count;
    int cal[1001][2];
} MyCalendar;


MyCalendar* myCalendarCreate() {
    MyCalendar *cal = (MyCalendar *)malloc(sizeof(MyCalendar));
    memset(cal,0,sizeof(MyCalendar));
    cal->count = 0;
    return cal;
}

void addCal(MyCalendar *obj, int pos, int start, int end)
{
    if (obj->count > 1000)
    {
        return;
    }

    int j = obj->count;
    while (j > pos)
    {
        obj->cal[j][0] = obj->cal[j-1][0];
        obj->cal[j][1] = obj->cal[j-1][1];
        j--;
    }
    obj->cal[pos][0] = start;
    obj->cal[pos][1] = end;
    obj->count++;

    return;
}
//  不使用排序，每次都暴力求冲突，遍历完不冲突则在最后增加；
bool myCalendarBook(MyCalendar* obj, int start, int end) {
    int i = 0;
    for (i = 0; i < obj->count; i++)
    {
        if (end <= obj->cal[i][0] || start >= obj->cal[i][1])
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    obj->cal[obj->count][0] = start;
    obj->cal[obj->count][1] = end;
    obj->count++;

    return true;
}

void myCalendarFree(MyCalendar* obj) {
    if (obj != NULL)
    {
        free(obj);
        obj = NULL;
    }
    return;
}

/**
 * Your MyCalendar struct will be instantiated and called as such:
 * MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, start, end);
 
 * myCalendarFree(obj);
*/
// @lc code=end


bool myCalendarBook(MyCalendar* obj, int start, int end) {
    int i = 0;
    for (i = 0; i < obj->count; i++)
    {
        if (start < obj->cal[i][1])
        {
            if (start >= obj->cal[i][0] || end > obj->cal[i][0]) //最刚开始end的判断错误用成cal[i][1]
            {
                return false;
            }
            else
            {
                addCal(obj,i,start,end);
                return true;
            }
        }
    }

    if (i == obj->count)
    {
        addCal(obj,i,start,end);
    }
    
    return true;
}