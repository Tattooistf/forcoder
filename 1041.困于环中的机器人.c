/*
 * @lc app=leetcode.cn id=1041 lang=c
 *
 * [1041] 困于环中的机器人
 *
 * https://leetcode-cn.com/problems/robot-bounded-in-circle/description/
 *
 * algorithms
 * Medium (46.76%)
 * Likes:    79
 * Dislikes: 0
 * Total Accepted:    6K
 * Total Submissions: 12.6K
 * Testcase Example:  '"GGLLGG"'
 *
 * 在无限的平面上，机器人最初位于 (0, 0) 处，面朝北方。机器人可以接受下列三条指令之一：
 * 
 * 
 * "G"：直走 1 个单位
 * "L"：左转 90 度
 * "R"：右转 90 度
 * 
 * 
 * 机器人按顺序执行指令 instructions，并一直重复它们。
 * 
 * 只有在平面中存在环使得机器人永远无法离开时，返回 true。否则，返回 false。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入："GGLLGG"
 * 输出：true
 * 解释：
 * 机器人从 (0,0) 移动到 (0,2)，转 180 度，然后回到 (0,0)。
 * 重复这些指令，机器人将保持在以原点为中心，2 为半径的环中进行移动。
 * 
 * 
 * 示例 2：
 * 
 * 输入："GG"
 * 输出：false
 * 解释：
 * 机器人无限向北移动。
 * 
 * 
 * 示例 3：
 * 
 * 输入："GL"
 * 输出：true
 * 解释：
 * 机器人按 (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ... 进行移动。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= instructions.length <= 100
 * instructions[i] 在 {'G', 'L', 'R'} 中
 * 
 * 
 */

// @lc code=start

// 技巧性太强了，解答不出来，关键的思路想不到：搞明白一轮走下来方向不变，则不可能回原点；也就是x=y=0,或者方向变化，就能回原点
bool isRobotBounded(char * instructions){
    int dir = 0;
    int dx[] = {0,1,0,-1};
    int dy[] = {1,0,-1,0};
    int x = 0;
    int y = 0;

    for (int i = 0; i < strlen(instructions); i++)
    {
        switch (instructions[i])
        {
            case 'G':
                dir = dir%4;
                x = x + dx[dir];
                y = y + dy[dir];
                break;
            
            case 'R':
                dir += 1;
                break;
            
            case 'L':
                dir += 3;
                break;

            default:
                break;
        }
    }
    return ((x == 0) && (y == 0)) || ((dir%4) != 0);
}
// @lc code=end

