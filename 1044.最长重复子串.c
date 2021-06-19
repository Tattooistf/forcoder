/*
 * @lc app=leetcode.cn id=1044 lang=c
 *
 * [1044] 最长重复子串
 *
 * https://leetcode-cn.com/problems/longest-duplicate-substring/description/
 *
 * algorithms
 * Hard (20.24%)
 * Likes:    83
 * Dislikes: 0
 * Total Accepted:    3.1K
 * Total Submissions: 14.8K
 * Testcase Example:  '"banana"'
 *
 * 给出一个字符串 S，考虑其所有重复子串（S 的连续子串，出现两次或多次，可能会有重叠）。
 * 
 * 返回任何具有最长可能长度的重复子串。（如果 S 不含重复子串，那么答案为 ""。）
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入："banana"
 * 输出："ana"
 * 
 * 
 * 示例 2：
 * 
 * 输入："abcd"
 * 输出：""
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= S.length <= 10^5
 * S 由小写英文字母组成。
 * 
 * 
 */

// @lc code=start

int comp(const void *a, const void *b)
{
    char *tmpa = *((char **)a);
    char *tmpb = *((char **)b);

    if (strcmp(tmpa, tmpb) > 0) // strcmp返回值使用错误，原本判断的是0和非0，应该判断1和-1
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

char * longestDupSubstring(char * S){
    char *a[100000] = {0};
    int i = 0;
    int lens = strlen(S); //再通过将所有的strlen提前计算终于满足要求
    while (*(S+i) != '\0')
    {
        a[i] = S+i;
        i++;
    }
    qsort(a,lens,sizeof(char **),comp);
    int idx = 0;
    int max = 0;
    char *pint = 0;
    for (int i = 0; i < lens-1; i++)
    {
        // len = cmpstr(a[i],a[i+1]);
        //  printf("%s,%s\n",a[i],a[i+1]);
        int len1 = strlen(a[i]); // 提前计算一次，避免下面的条件判断计算2次，节省时间
        int len2 = strlen(a[i+1]);
        int len = len1 > len2 ? len2 : len1;
        if (len <= max) // 增加过滤器，将len小于max的去除掉，节省时间，但最后一个不通过
        {
            continue;
        }
        
        idx = 0;
        while (idx < len && a[i][idx] == a[i+1][idx])
        {
            idx++;
        }
        if (idx > max)
        {
            pint = a[i];
            max = idx;
        }
    }
    char *ret = (char *)malloc(sizeof(char)*(max+1));
    memset(ret,0,sizeof(char)*(max+1));
    if (pint != 0)
    {
        strncpy(ret,pint,max);
    }
    ret[max] = '\0';
    return ret;
}
// @lc code=end

