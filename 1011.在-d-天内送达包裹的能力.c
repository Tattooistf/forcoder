/*
 * @lc app=leetcode.cn id=1011 lang=c
 *
 * [1011] 在 D 天内送达包裹的能力
 *
 * https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/description/
 *
 * algorithms
 * Medium (56.43%)
 * Likes:    373
 * Dislikes: 0
 * Total Accepted:    54.9K
 * Total Submissions: 87.5K
 * Testcase Example:  '[1,2,3,4,5,6,7,8,9,10]\n5'
 *
 * 传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
 * 
 * 传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
 * 
 * 返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：weights = [1,2,3,4,5,6,7,8,9,10], D = 5
 * 输出：15
 * 解释：
 * 船舶最低载重 15 就能够在 5 天内送达所有包裹，如下所示：
 * 第 1 天：1, 2, 3, 4, 5
 * 第 2 天：6, 7
 * 第 3 天：8
 * 第 4 天：9
 * 第 5 天：10
 * 
 * 请注意，货物必须按照给定的顺序装运，因此使用载重能力为 14 的船舶并将包装分成 (2, 3, 4, 5), (1, 6, 7), (8), (9),
 * (10) 是不允许的。 
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：weights = [3,2,2,4,1,4], D = 3
 * 输出：6
 * 解释：
 * 船舶最低载重 6 就能够在 3 天内送达所有包裹，如下所示：
 * 第 1 天：3, 2
 * 第 2 天：2, 4
 * 第 3 天：1, 4
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：weights = [1,2,3,1,1], D = 4
 * 输出：3
 * 解释：
 * 第 1 天：1
 * 第 2 天：2
 * 第 3 天：3
 * 第 4 天：1, 1
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
int f(int *arr, int size, int x) // 这个函数上花了很多时间，最后没有解决
{
    int day = 1;
    int weight = 0;
    for (int i = 0; i < size; i++)
    {
        weight += arr[i];
        if (weight > x)
        {
            day++;
            weight = arr[i];
        }
    }
    return day;
}

#define MAX(a,b) ((a) > (b)) ? (a):(b)
int shipWithinDays(int* weights, int weightsSize, int days){
    int left = 0;
    int right = 0;
    int sum = 0;
    int max = 0;
    for (int i = 0; i < weightsSize; i++)
    {
        max = MAX(max,weights[i]);
        sum += weights[i];
    }
    left = max;
    right = sum+1;
    
    while (left < right)
    {
        int mid = left + (right-left)/2;
        if (f(weights, weightsSize, mid) == days)
        {
            right = mid;
        }
        else if (f(weights, weightsSize, mid) < days)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return left;
}
// @lc code=end

