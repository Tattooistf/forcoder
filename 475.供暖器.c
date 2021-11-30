/*
 * @lc app=leetcode.cn id=475 lang=c
 *
 * [475] 供暖器
 *
 * https://leetcode-cn.com/problems/heaters/description/
 *
 * algorithms
 * Medium (31.81%)
 * Likes:    216
 * Dislikes: 0
 * Total Accepted:    20.8K
 * Total Submissions: 62.6K
 * Testcase Example:  '[1,2,3]\n[2]'
 *
 * 冬季已经来临。 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。
 * 
 * 在加热器的加热半径范围内的每个房屋都可以获得供暖。
 * 
 * 现在，给出位于一条水平线上的房屋 houses 和供暖器 heaters 的位置，请你找出并返回可以覆盖所有房屋的最小加热半径。
 * 
 * 说明：所有供暖器都遵循你的半径标准，加热的半径也一样。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: houses = [1,2,3], heaters = [2]
 * 输出: 1
 * 解释: 仅在位置2上有一个供暖器。如果我们将加热半径设为1，那么所有房屋就都能得到供暖。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: houses = [1,2,3,4], heaters = [1,4]
 * 输出: 1
 * 解释: 在位置1, 4上有两个供暖器。我们需要将加热半径设为1，这样所有房屋就都能得到供暖。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：houses = [1,5], heaters = [2]
 * 输出：3
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 
 * 
 */

// @lc code=start

// 错误：没有提前排序，解题超时，主要是func中暴力求解sum个数
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

int func(int *houses, int housesSize, int* heaters, int heatersSize, int val)
{
    int sum = 0;
    int j = 0;
    // for (int i = 0; i < housesSize; i++) // 错误：内外循环搞错了，导致计算的sum错误；
    // {
    //     for (; j < heatersSize; j++)
    //     {
    //         long left = heaters[j]-val;
    //         long right = heaters[j]+val;
    //         if (houses[i] >= left && houses[i] <= right)
    //         {
    //             sum++;
    //             break;
    //         }
    //     }
    // }

    for (int i = 0; i < heatersSize; i++)
    {
        long left = heaters[i]-val;
        long right = heaters[i]+val;
        while (j<housesSize)
        {
            if (houses[j] >= left && houses[j] <= right)
            {
                j++;
            }
            else
            {
                break;
            }
        }
    }
    
    return j;
}

int cmpmax(void *a, void *b)
{
    int *tmpa = (int*)a;
    int *tmpb = (int*)b;
    if (*tmpa < *tmpb)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int findRadius(int* houses, int housesSize, int* heaters, int heatersSize){
    qsort(houses,housesSize,sizeof(int),cmpmax);
    qsort(heaters,heatersSize,sizeof(int),cmpmax);

    int max = 0;
    max = MAX(houses[housesSize-1], heaters[heatersSize-1]);

    int left = 0; // 错误：需要考虑heater和houses位置重合的情况，也就是left要包含0；
    int right = max;
    while (left <= right)
    {
        long mid = left+(right-left)/2;
        if (func(houses,housesSize,heaters,heatersSize,mid) >= housesSize)
        {
            right = mid-1;
        }
        else
        {
            left = mid+1;
        }
    }
    return left;    
}
// @lc code=end


// 另外一种解题思路，排序后寻找左右最近值，再判断所有最值中的最大值即为结果
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

int cmpmax(void *a, void *b)
{
    int *tmpa = (int*)a;
    int *tmpb = (int*)b;
    if (*tmpa < *tmpb)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
#define INT_MAX 0x3fffffff
int findRadius(int* houses, int housesSize, int* heaters, int heatersSize){

    qsort(houses,housesSize,sizeof(int),cmpmax);
    qsort(heaters,heatersSize,sizeof(int),cmpmax);

    int ret = 0;
    for (int i = 0; i < housesSize; i++)
    {
        // 寻找最左值
        int left = 0;
        int right = heatersSize;
        while (left<right)
        {
            int mid = left+(right-left)/2;
            if (heaters[mid] >= houses[i])
            {
                right = mid;
            }
            else
            {
                left = mid+1; // 错误：搞错成了mid-1
            }
        }
        int dist = INT_MAX;// 最左值
        if (left <= 0)
        {
            dist = INT_MAX;
        }
        else
        {
            dist = abs(heaters[left-1]-houses[i]);
        }
        
        int dist2 = INT_MAX; // 最右值
        if (left >= heatersSize)
        {
            dist2 = INT_MAX;
        }
        else
        {
            dist2 = abs(heaters[left]-houses[i]);
        }
        
        ret = MAX(ret,MIN(dist,dist2));
    }
    return ret;    
}

