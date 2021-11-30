/*
 * @lc app=leetcode.cn id=794 lang=c
 *
 * [794] 有效的井字游戏
 *
 * https://leetcode-cn.com/problems/valid-tic-tac-toe-state/description/
 *
 * algorithms
 * Medium (33.74%)
 * Likes:    34
 * Dislikes: 0
 * Total Accepted:    7.1K
 * Total Submissions: 20.9K
 * Testcase Example:  '["O  ","   ","   "]'
 *
 * 用字符串数组作为井字游戏的游戏板 board。当且仅当在井字游戏过程中，玩家有可能将字符放置成游戏板所显示的状态时，才返回 true。
 * 
 * 该游戏板是一个 3 x 3 数组，由字符 " "，"X" 和 "O" 组成。字符 " " 代表一个空位。
 * 
 * 以下是井字游戏的规则：
 * 
 * 
 * 玩家轮流将字符放入空位（" "）中。
 * 第一个玩家总是放字符 “X”，且第二个玩家总是放字符 “O”。
 * “X” 和 “O” 只允许放置在空位中，不允许对已放有字符的位置进行填充。
 * 当有 3 个相同（且非空）的字符填充任何行、列或对角线时，游戏结束。
 * 当所有位置非空时，也算为游戏结束。
 * 如果游戏结束，玩家不允许再放置字符。
 * 
 * 
 * 
 * 示例 1:
 * 输入: board = ["O  ", "   ", "   "]
 * 输出: false
 * 解释: 第一个玩家总是放置“X”。
 * 
 * 示例 2:
 * 输入: board = ["XOX", " X ", "   "]
 * 输出: false
 * 解释: 玩家应该是轮流放置的。
 * 
 * 示例 3:
 * 输入: board = ["XXX", "   ", "OOO"]
 * 输出: false
 * 
 * 示例 4:
 * 输入: board = ["XOX", "O O", "XOX"]
 * 输出: true
 * 
 * 
 * 说明:
 * 
 * 
 * 游戏板 board 是长度为 3 的字符串数组，其中每个字符串 board[i] 的长度为 3。
 * board[i][j] 是集合 {" ", "X", "O"} 中的一个字符。
 * 
 * 
 */

// @lc code=start

int check(char **board, int boardSize)
{
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X')
        || (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O'))
        {
            return true;
        }

        if ((board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X')
        ||(board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O'))
        {
            return true;
        }        
    }
    
    if ((board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
    || (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O'))
    {
        return true;
    }
    
    if ((board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
    || (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O'))
    {
        return true;
    }

    return false;    
}
#define NUM 9

int equal(char **board, int boardSize, char **arr)
{
    for (int i = 0; i < NUM; i++)
    {
        int x = i/boardSize;
        int y = i%boardSize;
        if (board[x][y] != arr[x][y])
        {
            return false;
        }
    }
    return true;
}

int ret = false;
void backtrace(char **board, int boardSize, int flag, int level, char **arr)
{   
    if (ret == true)
    {         
        return;
    }
    
    if (level <= 0 || true == check(arr,boardSize)) //错误： check函数对象搞错成board，应该是arr
    {
        if (equal(board,boardSize,arr) == true)
        {
            ret = true;
        }  
        return;
    }
    
    for (int i = 0; i < NUM; i++)
    {
        int x = i/boardSize;
        int y = i%boardSize;
        if (board[x][y] == ' ' || arr[x][y] != ' ')
        {
            continue;
        }
        arr[x][y] = (flag == 0)?'X':'O';
        backtrace(board,boardSize,~flag,level-1,arr);     
        arr[x][y] = ' ';
    }
    
    return;
}

// 错误：理解题目错误，以为是在空闲的地方填符号；后面对arr的申请又搞错了，用全局变量定义，导致访问不可写的内存；
// 栽过坑，全局变量没有每次都初始化
bool validTicTacToe(char ** board, int boardSize){
    int count = 0;
    char **arr = (char **)malloc(sizeof(char *)*3);
    for (int i = 0; i < 3; i++)
    {
        arr[i] = (char *)malloc(sizeof(char)*4);
        memset(arr[i],0,sizeof(char)*4);
        for (int j = 0; j < 3; j++)
        {
            arr[i][j] = ' ';
        }
    }
    
    for (int i = 0; i < NUM; i++)
    {
        int x = i/boardSize;
        int y = i%boardSize;
        if (board[x][y] != ' ')
        {
            count++;
        }
    }
    
    int xflag = 0;
    ret = false;
    backtrace(board,boardSize,xflag,count,arr);
    
    return ret;
}
// @lc code=end

