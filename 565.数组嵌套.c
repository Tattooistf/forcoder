/*
 * @lc app=leetcode.cn id=565 lang=c
 *
 * [565] 数组嵌套
 *
 * https://leetcode-cn.com/problems/array-nesting/description/
 *
 * algorithms
 * Medium (60.22%)
 * Likes:    153
 * Dislikes: 0
 * Total Accepted:    12.4K
 * Total Submissions: 20.4K
 * Testcase Example:  '[5,4,0,3,1,6,2]'
 *
 * 索引从0开始长度为N的数组A，包含0到N - 1的所有整数。找到最大的集合S并返回其大小，其中 S[i] = {A[i], A[A[i]],
 * A[A[A[i]]], ... }且遵守以下的规则。
 * 
 * 假设选择索引为i的元素A[i]为S的第一个元素，S的下一个元素应该是A[A[i]]，之后是A[A[A[i]]]...
 * 以此类推，不断添加直到S出现重复的元素。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 输入: A = [5,4,0,3,1,6,2]
 * 输出: 4
 * 解释: 
 * A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.
 * 
 * 其中一种最长的 S[K]:
 * S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * N是[1, 20,000]之间的整数。
 * A中不含有重复的元素。
 * A中的元素大小在[0, N-1]之间。
 * 
 * 
 */

// @lc code=start
/* 下面的是常规解题思路，不是太好，使用了visit后才勉强通过；最好使用并查集的方式 */
int visit[20000] = {0};
int arrayNesting(int* nums, int numsSize){
    int max = 0;
    memset(visit,0,sizeof(int)*20000);  /* 容易忘记全局变量的初始化，否则会残留到下个用例 */
    for (int i = 0; i < numsSize; i++)
    {
        int a = nums[i];
        int count = 1;
        if (visit[a] == 1)
        {
            continue;
        }
        
        while (nums[i] != nums[a])
        {
            count++;
            visit[a] = 1;
            a = nums[a];
        }
        max = count>max?count:max;
    }
    
    return max;
}
// @lc code=end


// 比较到位的解法，并查集解决；出现的问题，size数组应该初始化为1；find和merge有点生疏，不知道用哪个数组，逻辑也有点不清楚
int parent[20000] = {0};
int tree[20000] = {0};
int size[20000] = {1};

int find(int val)
{
    int x = parent[val];
    if (val != x)
    {
        x = find(x);
    }
    return x;
}

void merge(int a, int b)
{
    int parenta = find(a);
    int parentb = find(b);
    if (parenta == parentb)
    {
        return;
    }

    if (tree[parentb] < tree[parenta]) /* tree代表的路径压缩实际上可以考虑不用的 */
    {
        parent[parentb] = parenta;
        size[parenta] += size[parentb];
        size[parentb] = 0; /* 不用考虑置0效果是一样的 */
    }
    else
    {
        parent[parenta] = parentb;
        if (tree[parenta] == tree[parentb])
        {
            tree[parentb]++;
        }
        size[parentb] += size[parenta];
        size[parenta] = 0;
    }
    return;
}

int arrayNesting(int* nums, int numsSize){
    for (int i = 0; i < numsSize; i++)
    {
        parent[nums[i]] = nums[i];
        size[nums[i]] = 1;
    }

    for (int i = 0; i < numsSize; i++)
    {
        merge(nums[i], nums[nums[i]]);
    }

    int max = 0;
    for (int i = 0; i < numsSize; i++)
    {
        max = (size[i] > max)? size[i] : max;
    }
    return max;
}