/*
 * @lc app=leetcode.cn id=621 lang=c
 *
 * [621] 任务调度器
 *
 * https://leetcode-cn.com/problems/task-scheduler/description/
 *
 * algorithms
 * Medium (47.13%)
 * Likes:    192
 * Dislikes: 0
 * Total Accepted:    13.4K
 * Total Submissions: 28.2K
 * Testcase Example:  '["A","A","A","B","B","B"]\n2'
 *
 * 给定一个用字符数组表示的 CPU 需要执行的任务列表。其中包含使用大写的 A - Z 字母表示的26
 * 种不同种类的任务。任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。CPU
 * 在任何一个单位时间内都可以执行一个任务，或者在待命状态。
 * 
 * 然而，两个相同种类的任务之间必须有长度为 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。
 * 
 * 你需要计算完成所有任务所需要的最短时间。
 * 
 * 示例 1：
 * 
 * 
 * 输入: tasks = ["A","A","A","B","B","B"], n = 2
 * 输出: 8
 * 执行顺序: A -> B -> (待命) -> A -> B -> (待命) -> A -> B.
 * 
 * 
 * 注：
 * 
 * 
 * 任务的总个数为 [1, 10000]。
 * n 的取值范围为 [0, 100]。
 * 
 * 
 */
// 之前在公司的时候解答过，主要是最佳解的模型一定是与最长个数出现的次数相关
// 也就是说最后放的一定是最长的，并且是间隔放的。答案从leastIntervalc中提取出来
// @lc code=start


int leastInterval(char* tasks, int tasksSize, int n){

}


// @lc code=end


int leastInterval(char* tasks, int tasksSize, int n){
    char num[26][2]={0};
    int i,k;
    int j=0;
    int cnt=0;
    char res[10000]={'0'};
    char tmp[2]={0};
    
    for(i=0;i<tasksSize;i++)
    {
        for(k=0;k<cnt;k++)
        {
            if(num[k][0] == tasks[i]) {num[k][1]++;break;}
        }
        if(k>=cnt)
        {
            num[k][0]=tasks[i];
            num[k][1]++;
            cnt++;
        }
    }

    for(i=0;i<cnt;i++)
    {
        for(k=i+1;k<cnt;k++)
        {
            if(num[k][1]>num[i][1])
            {
                tmp[1]=num[i][1];
                num[i][1]=num[k][1];
                num[k][1]=tmp[1];
                tmp[0]=num[i][0];
                num[i][0]=num[k][0];
                num[k][0]=tmp[0];
            }
        }
    }
    
    j=cnt;
    cnt=0;
    while(1)
    {        
        for(k=0;k<j;k++)
        {
            res[cnt++]=num[k][0];
            num[k][1]--;
        }
        if(num[0][1]==0) break;//cnt==tasksSize        
        for(k=0;k<n-j+1;k++)
        {
            res[cnt++]='a';
        }
        if(num[j-1][1]==0) j--;
    }
    return cnt;
}


int leastInterval2(char* tasks, int tasksSize, int n){
    int num[26]={0};
    int i,index;
    int max=0;
    int cnt=0;
    int len=0;
    
    if(n==0) return tasksSize;
    
    for(i=0;i<tasksSize;i++)
    {
        index = tasks[i]-'A';
        num[index]++;
        if(max<num[index])
        {
            max=num[index];
        }
    }
    for(i=0;i<26;i++)
    {
        if(max==num[i])
        {
            cnt++;
        }
    }
    if(cnt>n) return tasksSize;
    
    return (max-1)*(n+1)+cnt;
}


int leastInterval3(char* tasks, int tasksSize, int n){
    int num[26]={0};
    int i,index,k;
    int max=0;
    int cnt=0;
    int maxcnt=0;
    int len=0;
    
    if(n==0) return tasksSize;
    
    for(i=0;i<tasksSize;i++)
    {
        index = tasks[i]-'A';
        num[index]++;
        if(max<num[index])
        {
            max=num[index];
        }
    }
    
    k=max;
    do
    {
        cnt=0;
        for(i=0;i<26;i++)
        {
            if(k==num[i])
            {
                cnt++;
                if(k==max) maxcnt=cnt;
            }
        }
        if(cnt>n) return tasksSize;
    }while(--k>n);
    
    //printf("%d,%d,%d",max,maxcnt,len);
    return (max-1)*(n+1)+maxcnt;
}