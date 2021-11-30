/*
 * @lc app=leetcode.cn id=731 lang=c
 *
 * [731] 我的日程安排表 II
 *
 * https://leetcode-cn.com/problems/my-calendar-ii/description/
 *
 * algorithms
 * Medium (50.28%)
 * Likes:    83
 * Dislikes: 0
 * Total Accepted:    3.5K
 * Total Submissions: 6.9K
 * Testcase Example:  '["MyCalendarTwo","book","book","book","book","book","book"]\n' +
  '[[],[10,20],[50,60],[10,40],[5,15],[5,10],[25,55]]'
 *
 * 实现一个 MyCalendar 类来存放你的日程安排。如果要添加的时间内不会导致三重预订时，则可以存储这个新的日程安排。
 * 
 * MyCalendar 有一个 book(int start, int end)方法。它意味着在 start 到 end
 * 时间内增加一个日程安排，注意，这里的时间是半开区间，即 [start, end), 实数 x 的范围为，  start <= x < end。
 * 
 * 当三个日程安排有一些时间上的交叉时（例如三个日程安排都在同一时间内），就会产生三重预订。
 * 
 * 每次调用 MyCalendar.book方法时，如果可以将日程安排成功添加到日历中而不会导致三重预订，返回 true。否则，返回 false
 * 并且不要将该日程安排添加到日历中。
 * 
 * 请按照以下步骤调用MyCalendar 类: MyCalendar cal = new MyCalendar();
 * MyCalendar.book(start, end)
 * 
 * 
 * 
 * 示例：
 * 
 * MyCalendar();
 * MyCalendar.book(10, 20); // returns true
 * MyCalendar.book(50, 60); // returns true
 * MyCalendar.book(10, 40); // returns true
 * MyCalendar.book(5, 15); // returns false
 * MyCalendar.book(5, 10); // returns true
 * MyCalendar.book(25, 55); // returns true
 * 解释： 
 * 前两个日程安排可以添加至日历中。 第三个日程安排会导致双重预订，但可以添加至日历中。
 * 第四个日程安排活动（5,15）不能添加至日历中，因为它会导致三重预订。
 * 第五个日程安排（5,10）可以添加至日历中，因为它未使用已经双重预订的时间10。
 * 第六个日程安排（25,55）可以添加至日历中，因为时间 [25,40] 将和第三个日程安排双重预订；
 * 时间 [40,50] 将单独预订，时间 [50,55）将和第二个日程安排双重预订。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 每个测试用例，调用 MyCalendar.book 函数最多不超过 1000次。
 * 调用函数 MyCalendar.book(start, end)时， start 和 end 的取值范围为 [0, 10^9]。
 * 
 * 
 */

// @lc code=start

// 思路大体正确，暴力法，存储二层冲突，分别判断一层冲突和二层冲突

typedef struct {
    int count;
    int count2;
    int cal[1001][2];
    int cal2[1001][2];
} MyCalendarTwo;


MyCalendarTwo* myCalendarTwoCreate() {
    MyCalendarTwo *cal = (MyCalendarTwo *)malloc(sizeof(MyCalendarTwo));
    memset(cal, 0, sizeof(MyCalendarTwo));
    return cal;
}
bool docal2(MyCalendarTwo* obj, int start, int end);

bool myCalendarTwoBook(MyCalendarTwo* obj, int start, int end) {
    if (obj->count > 1000)
    {
        return false;
    }

    // 此处需要先判断二层冲突；如果先判断一层冲突会错误，没搞清楚原因，可能是会导致错误添加无用的信息
    // 二层冲突失败的项，如果先判断一层的话，容易将不需要的信息添加到二层中来
    if (docal2(obj,start,end) == false)
    {
        return false;
    }

    for (int i = 0; i < obj->count; i++)
    {
        if (obj->cal[i][0] >= end || obj->cal[i][1] <= start)
        {
            continue;
        }
        else
        {
            int s1 = start > obj->cal[i][0] ? start : obj->cal[i][0];
            int e1 = end > obj->cal[i][1] ? obj->cal[i][1] : end;
            // docal2(obj,s1,e1);
            // 前面已经判断过不冲突，本处只需要增加表项就行
            obj->cal2[obj->count2][0] = s1;
            obj->cal2[obj->count2][1] = e1;
            obj->count2++;
            // if (docal2(obj,s1,e1) == true)
            // {
            //     continue;
            // }
            // else
            // {
            //     return false;
            // }
        }
    }
    obj->cal[obj->count][0] = start;
    obj->cal[obj->count][1] = end;
    obj->count++;

    return true;
}


bool docal2(MyCalendarTwo* obj, int start, int end) {
    if (obj->count2 > 1000)
    {
        return false;
    }

    for (int i = 0; i < obj->count2; i++)
    {
        if (obj->cal2[i][0] >= end || obj->cal2[i][1] <= start)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    // 没有注意到第一次判断的时候会重复添加，所以注释掉
    // obj->cal2[obj->count2][0] = start;
    // obj->cal2[obj->count2][1] = end;
    // obj->count2++;

    return true;
}


void myCalendarTwoFree(MyCalendarTwo* obj) {
    if (obj != NULL)
    {
        free(obj);
        obj = NULL;
    }
    return;
}

/**
 * Your MyCalendarTwo struct will be instantiated and called as such:
 * MyCalendarTwo* obj = myCalendarTwoCreate();
 * bool param_1 = myCalendarTwoBook(obj, start, end);
 
 * myCalendarTwoFree(obj);
*/
// @lc code=end

