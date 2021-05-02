/*
 * @lc app=leetcode.cn id=780 lang=c
 *
 * [780] 到达终点
 *
 * https://leetcode-cn.com/problems/reaching-points/description/
 *
 * algorithms
 * Hard (28.44%)
 * Likes:    90
 * Dislikes: 0
 * Total Accepted:    2.7K
 * Total Submissions: 9.7K
 * Testcase Example:  '9\n5\n12\n8'
 *
 * 从点 (x, y) 可以转换到 (x, x+y)  或者 (x+y, y)。
 * 
 * 给定一个起点 (sx, sy) 和一个终点 (tx, ty)，如果通过一系列的转换可以从起点到达终点，则返回 True ，否则返回 False。
 * 
 * 
 * 示例:
 * 输入: sx = 1, sy = 1, tx = 3, ty = 5
 * 输出: True
 * 解释:
 * 可以通过以下一系列转换从起点转换到终点：
 * (1, 1) -> (1, 2)
 * (1, 2) -> (3, 2)
 * (3, 2) -> (3, 5)
 * 
 * 输入: sx = 1, sy = 1, tx = 2, ty = 2
 * 输出: False
 * 
 * 输入: sx = 1, sy = 1, tx = 1, ty = 1
 * 输出: True
 * 
 * 
 * 
 * 注意:
 * 
 * 
 * sx, sy, tx, ty 是范围在 [1, 10^9] 的整数。
 * 
 * 
 */

// @lc code=start

//利用数学技巧，采用模的方式求解 nX+mY=aZ
bool reachingPoints(int sx, int sy, int tx, int ty){

    while(sx<tx && sy<ty) //可以使用while进行辗转取余
    {
        if (ty>tx)  //tx/ty = x+y
        {
            ty = ty%tx;
        }
        else
        {
            tx = tx%ty;
        }
    }

    if (sx>tx || sy>ty)
    {
        return false;
    }

    return ((tx-sx)%sy == 0)&&((ty-sy)%sx == 0); 
}

// @lc code=end


// 不知道什么原因会出现堆栈溢出，常规解题思路是正确的，但会出现超时；堆栈溢出怀疑嵌套调用太多
int backtrace(double x,double y,double dx,double dy)
{
    if (x>dx || y>dy)
    {
        return false;
    }    
    if (x == dx && y == dy)
    {
        return true;
    }

    if(true == backtrace(x+y,y,dx,dy))
    {
        return true;
    }

    if(true == backtrace(x,x+y,dx,dy))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool reachingPoints(int sx, int sy, int tx, int ty){
    return backtrace(sx,sy,tx,ty); 
}


//利用数学技巧，采用模的方式求解 nX+mY=aZ
bool reachingPoints(int sx, int sy, int tx, int ty){
    if (sx>tx || sy>ty)
    {
        return false;
    }
    if (sx == tx && sy == ty)
    {
        return true;
    }

    if(sx<tx && sy<ty) //可以使用while进行辗转取余
    {
        if (ty>tx)  //tx/ty = x+y
        {
            //ty = ty%tx;
            return reachingPoints(sx,sy,tx,ty%tx);
        }
        else if (tx>ty)
        {
            //tx = tx%ty;
            return reachingPoints(sx,sy,tx%ty,ty);
        }
    }

    return ((tx-sx)%sy == 0)&&((ty-sy)%sx == 0); 
}
