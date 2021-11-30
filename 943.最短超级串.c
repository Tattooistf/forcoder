/*
 * @lc app=leetcode.cn id=943 lang=c
 *
 * [943] 最短超级串
 *
 * https://leetcode-cn.com/problems/find-the-shortest-superstring/description/
 *
 * algorithms
 * Hard (45.77%)
 * Likes:    73
 * Dislikes: 0
 * Total Accepted:    1.4K
 * Total Submissions: 3.1K
 * Testcase Example:  '["alex","loves","leetcode"]'
 *
 * 给定一个字符串数组 words，找到以 words 中每个字符串作为子字符串的最短字符串。如果有多个有效最短字符串满足题目条件，返回其中 任意一个
 * 即可。
 * 
 * 我们可以假设 words 中没有字符串是 words 中另一个字符串的子字符串。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：words = ["alex","loves","leetcode"]
 * 输出："alexlovesleetcode"
 * 解释："alex"，"loves"，"leetcode" 的所有排列都会被接受。
 * 
 * 示例 2：
 * 
 * 
 * 输入：words = ["catg","ctaagt","gcta","ttca","atgcatc"]
 * 输出："gctaagttcatgcatc"
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * words[i] 由小写英文字母组成
 * words 中的所有字符串 互不相同
 * 
 * 
 */

// @lc code=start
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
int overLength(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = 0;

    for (int i = 0; i < MIN(len1,len2); i++)
    {
        int j = 0;
        for (j = 0; j < i; j++)
        {
            if (str1[len1-i+j] != str2[j])
            {
                break;
            }
        }
        if (j == i)
        {
            len = MAX(len, i);
        }
    }
    
    return len;
}
int mlen = 0xffffffff;
void dfs(char **words, int size, int level, int used, int len, int **order,int **over)
{
    if (len >= mlen)
    {
        return;
    }
    
    if (level == size)
    {
        mlen = len;
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (used & (1<<i))
        {
            continue;
        }

        (*order)[level] = i;
        int curlen = (level == 0)?strlen(words[0]):strlen(words[i])+len-over[(*order)[level-1]][i];
        dfs(words,size,level+1,used|(1<<i),curlen,order,over);
    }
    
    return;
}

char * shortestSuperstring(char ** words, int wordsSize){
    int **over = (int **)malloc(sizeof(int*)*wordsSize);
    for (int i = 0; i < wordsSize; i++)
    {
        over[i] = (int *)malloc(sizeof(int)*wordsSize);
        for (int j = 0; j < wordsSize; j++)
        {
            over[i][j] = overLength(words[i],words[j]);
        }
    }
    int *ret = (int *)malloc(sizeof(int)*wordsSize);
    dfs(words,wordsSize,0,0,0,&ret,over);

    char *str = (char *)malloc(sizeof(char)*(mlen+1));
    char *strtmp = str;
    for (int i = 0; i < wordsSize; i++)
    {
        if (i == 0)
        {
            strcpy(strtmp,words[ret[i]]);
            strtmp += strlen(words[ret[i]]);
        }
        else
        {
            strcpy(strtmp,words[ret[i]]+over[ret[i-1]][ret[i]]);
            strtmp += strlen(words[ret[i]])-over[ret[i-1]][ret[i]];
        }
    }
    *strtmp = '\0';
    return str;
}
// @lc code=end

