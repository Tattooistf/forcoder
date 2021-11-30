/*
 * @lc app=leetcode.cn id=864 lang=c
 *
 * [864] 获取所有钥匙的最短路径
 *
 * https://leetcode-cn.com/problems/shortest-path-to-get-all-keys/description/
 *
 * algorithms
 * Hard (43.57%)
 * Likes:    79
 * Dislikes: 0
 * Total Accepted:    2.5K
 * Total Submissions: 5.7K
 * Testcase Example:  '["@.a.#","###.#","b.A.B"]'
 *
 * 给定一个二维网格 grid。 "." 代表一个空房间， "#" 代表一堵墙， "@" 是起点，（"a", "b", ...）代表钥匙，（"A",
 * "B", ...）代表锁。
 * 
 * 
 * 我们从起点开始出发，一次移动是指向四个基本方向之一行走一个单位空间。我们不能在网格外面行走，也无法穿过一堵墙。如果途经一个钥匙，我们就把它捡起来。除非我们手里有对应的钥匙，否则无法通过锁。
 * 
 * 假设 K 为钥匙/锁的个数，且满足 1 <= K <= 6，字母表中的前 K
 * 个字母在网格中都有自己对应的一个小写和一个大写字母。换言之，每个锁有唯一对应的钥匙，每个钥匙也有唯一对应的锁。另外，代表钥匙和锁的字母互为大小写并按字母顺序排列。
 * 
 * 返回获取所有钥匙所需要的移动的最少次数。如果无法获取所有钥匙，返回 -1 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：["@.a.#","###.#","b.A.B"]
 * 输出：8
 * 
 * 
 * 示例 2：
 * 
 * 输入：["@..aA","..B#.","....b"]
 * 输出：6
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= grid.length <= 30
 * 1 <= grid[0].length <= 30
 * grid[i][j] 只含有 '.', '#', '@', 'a'-'f' 以及 'A'-'F'
 * 钥匙的数目范围是 [1, 6]，每个钥匙都对应一个不同的字母，正好打开一个对应的锁。
 * 
 * 
 */

// @lc code=start
typedef struct POINT
{
    int i;
    int j;
    int k;
} POINT;
// 可以使用指针的结构体队列，队列自行申请内存存储数据；出入队列传递指针的方式

int Wr = 0;
int Rd = 0;
int Cnt = 0;
#define MAX 900
POINT Q[MAX] = {0};

void QueueInit(void)
{
    Wr = 0;
    Rd = 0;
    Cnt = 0;
    memset(Q,0,sizeof(POINT)*MAX);
    return;
}

int EnQueue(POINT val)
{
    if (Cnt >= MAX)
    {
        return -1;
    }
    memcpy(&Q[Wr],&val,sizeof(POINT));
    //Q[Wr] = val;
    Wr = (Wr+1)%MAX;
    Cnt++;
    return 0;
}

POINT DeQueue(void)
{
    if (Cnt <= 0)
    {
        return -1;
    }
    POINT ret;
    memcpy(&ret,&Q[Rd],sizeof(POINT));
    //int ret = Q[Rd];
    Rd = (Rd+1)%MAX;
    Cnt--;
    return ret;
    
}

int QueueEmpty(void)
{
    return (Cnt == 0)?1:0;
}


int shortestPathAllKeys(char ** grid, int gridSize){
    int mask = 0;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < strlen(grid[i]); j++)
        {
            if (grid[i][j] >= 'a' && grid[i][j] <= 'f')
            {
                mask |= 1 << (grid[i][j]-'a');
            }
            if (grid[i][j] == '@')
            {
                EnQueue(i,j,0);
            }
        }     
    }

    while (!QueueEmpty())
    {
        int point = DeQueue();
        if (point.k == mask)
        {
            return point.d;
        }
        
        int Dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        for (int i = 0; i < 4; i++)
        {
            int row = point.i+Dir[i][0];
            int col = point.j+Dir[i][1];
            if (!visit[row][col][point.k] && grid[row][col]!='#')
            {
                if (grid[row][col]>='A' 
                    && grid[row][col]<='F'
                    &&(!point.k&(1<<(gird[row][col]-'A'))))
                {
                    continue;
                }

                if (grid[row][col]>='a'&&grid[row][col]<='f')
                {
                    point2.k |= 1<<(grid[row][col]-'a');
                }
                
                visit[row][col][point2.k]=1;
                EnQueue(row,col,point2.k,d+1);
                
            }
            
        }
        
    }
    
    return 0;
}


// @lc code=end

