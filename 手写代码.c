int find(int x)
{
    int res = x;
    if(set[x] == x)
        return x;
    res = find(set[x]); // set[x] = find(set[x])

    while(x != res)
    {
        int p = set[x];
        set[x] = res;
        x = p;
    }
    return x; //set[x]
}

void unionset(int x, int y)
{
    if((x=find(x)) == (y=find(y))) return;
    //set[x] = y;

    if(tree[x] < tree[y]) // set[y] < set[x] set[y]+=set[x]
    {
        set[x] = y;
    }
    else // set[x]+=set[y] set[y]=x;
    {
        set[y] = x;
        if(tree[x] == tree[y]) tree[x]++;
    }
    return;
}


//字典树

int array[5000][26];
int color[5000];
int k = 0;

void insert(char *s)
{
    int p=0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (array[p][s[i]-'a'] == -1)
        {
            array[p][s[i]-'a'] = k;
            k++;
        }
        p = array[p][s[i]-'a'];        
    }
    color[p] = 1;
    
    return;
}

int find(char *s)
{
    int p = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (array[p][s[i]-'a'] == -1)
        {
            return -1;
        }
        p = array[p][s[i]-'a'];
    }
    return (color[p] == 1);
}


//桶排序
void sortbullet(int *array,int bulletcnt)
{
    for (int i = 0; i < count; i++)
    {
        min = array[i]<min?array[i]:min;
        max = array[i]>max?array[i]:max;
    }
    int space = (max-min+1)/bulletcnt;
    for (int i = 0; i < count; i++)
    {
        int index = (array[i] - min)/space;
        if (bucket[index] != 0)
        {
            int j = bucket[index].len;
            while (j >= 0 && bucket[index][j]>array[i])
            {
                bucket[index][j+1] = bucket[index][j];
            }
            bucket[index][j] = array[i];
        }
        else
        {
            bucket[index][0] = array[i];
            bucket[index].len = 1;
        }
    }

    while (index < bulletcnt)
    {
        if (bucket[index] != 0)
        {
            array[] = bucket[index];
        }
        index++;
    }
}


void dfs(int node,int *g_v)
{
    int val = node;
    node = g_v[node]->head;
    while(node)
    {
        if (!isvisit(node->dest))
        {
            dfs(node->dest,g_v);
        }
        node = node->next;
    }
    push(val);
    return;
}

void toposort(int *g_v)
{
    for (int i = 0; i < count; i++)
    {
        if (!isvisit(i))
        {
            dfs(i,g_v);
        }  
    }
    
    while (!isempty(stack))
    {
        pop();
        printf();
    }
    
    return;
}


void selectsort(int *array)
{
    for (int i = 0; i < count; i++)
    {
        min = i;
        for (int j = i+1; j < count; j++)
        {
            min = array[j]>array[min]?min:j;
        }
        if (min != i)
        {
            swap(min,i);
        }  
    }
    
    return;
}

void insertsort(int *array)
{
    for (int i = 1; i < count; i++)
    {
        int j = i-1;
        while (j>=0 && array[j]>array[i])
        {
            array[j+1] = array[j];
            j--;
        }
        array[j] = array[i];
    }
    return;
}

void basesort(int *array)
{
    for (int i = 0; i < count; i++)
    {
        max = max>array[i]?max:array[i];
    }
    for (int i = 1; i < max; i*=10)
    {
        cntsort(i);
    }
    
    return;
}

void cntsort(int divider)
{
    int cnt[10] = {0};
    for (int i = 0; i < count; i++)
    {
        cnt[array[i]/divider%10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        cnt[i] += cnt[i-1];
    }

    int res[xx];
    for (int i = count-1; i >= 0; i--)
    {
        int idx = array[i]/divider%10;
        res[--cnt[idx]] = array[i];
    }

    for (int i = 0; i < count; i++)
    {
        array[i] = res[i];
    }
    
    return;   
}

void quicksort(int *array,int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int i = left;
    int j = right;
    int key = array[left];
    while (i<j)
    {
        while (i<j && key<array[j])
        {
            j--;
        }
        while (i<j && key>=array[i])
        {
            i++;
        }
        swap(i,j);
    }
    swap(left,j); // 交换中间的值
    quicksort(array,left,i-1);
    quicksort(array,i+1,right);
    
    return;
}


// 滑动窗口 框架代码
int splitwindows(char *array)
{
    int right = 0;
    int left = 0;
    int cnt = 0;
    for (int i = 0; i < sizeof(array); i++)
    {
        need[array[i]]++;
    }
    
    while (right < sizeof(array))
    {
        char m = array[right];
        right++;
        if (need[m])
        {
            windows[m]++;
            if (need[m] == windows[m])
            {
                cnt++;
            }
            
        }
        while (needcnt == cnt)
        {
            char n = array[left];
            left++;
            if (need[n])
            {
                if (need[n] == windows[n])
                {
                    cnt--;
                }
                windows[n]--;
                
            }
            
        }
        
        
    }
    
    return 0;
}

while(i<lena && j<lenb)
{
    if (!(b1>a2 || b2<a1))
    {
        a=max(a1,b1);
        b=min(a2,b2);
    }
    if (a2>b2)
    {
        j++;
    }
    else
    {
        i++;
    }
}

void sort(int A[],int count)
{
    for (int i = 0; i < count; i++)
    {
        if (maxv < A[i])
        {
            maxv = A[i];
            maxc = i;
        }
    }

    reverse(A,0,maxc);
    record[p++] = maxc+1;

    reverse(A,0,count-1);
    record[p++] = count;

    sort(A,count-1);
    return;
}

void reverse(int A[],int a,int b)
{
    while (a < b)
    {
        int tmp = A[a];
        A[a] = A[b];
        A[b] = tmp;
        a++;
        b--;
    }
    
    return;
}

//数组中存在环
for (int i = 0; i < count; i++)
{
    loop++;
    for (int j = i; temp[j] == 0; j = array[j])
    {
        temp[j] = 1;
    }
    
}

int binserach(int A[],int tar)
{
    int left = 0;
    int right = sizeof(A)-1;
    while (left<=right)
    {
        int mid = left+(right-left)/2;
        if (A[mid] == tar)
        {
            return mid;
        }
        else if(A[mid] < tar)
        {
            left = mid + 1;
        }
        else if (A[mid] > tar)
        {
            right = mid -1;
        }
    }
    
    return -1;
}


int find(int p)
{
    while (p!=parent[p])
    {
        p = parent[p];
        //parent[p] = parent[parent[p]];
        // p = parent[p];
    }
    if (p!=parent[p])
    {
        parent[p] = find(parent[p]);
    }// return parent[p];
    
    return p;
}

int union(int p,int q)
{
    int parP = find(p);
    int parQ = find(q);
    if (parP == parQ)
    {
        return;
    }

    if (rank[parP]<rank[parQ])
    {
        parent[parP] = parQ;
    }
    else if(rank[parQ]<rank[parP])
    {
        parent[parQ] = parP;
    }
    else
    {
        parent[parQ] = parP;
        rank[parP]++;
    }
    return;    
}

boolean backtrace(char board[][],int i, int j)
{
    int m = 9, n = 9;
    if(j == n) return backtrace(board,i+1,0);
    if(i == m) return true;
    if(board[i][j] != '.')
    {
        return backtrace(board,i,j+1);
    }

    for(char k = '1';k<='9';k++)
    {
        if(!isValid(k)) continue;
        board[i][j] = k;
        if(backtrace(board,i,j+1))
        {
            return true;
        }
        board[i][j] = '.';
    }
    return false;
}

boolean isValid(char board[][],int i,int j,char ch)
{
    for(int u=0;u<9;u++)
    {
        if(board[i][u] == ch) return false;
        if(board[u][j] == ch) return false;
        if(board[(i/3)*3+u/3][(j/3)*3+u%3] == ch) return false;
    }
    return ture;
}


void sort(int *a, int left, int right)
{
    if(left>=right)
    {
        return;
    }
    int i = left;
    int j = right;
    int key = a[left];

    while(i<j)
    {
        while(i<j && key<=a[j])
        {
            j--;
        }
        a[i] = a[j];

        while(i<j && key>=a[i])
        {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    sort(a,left,i-1);
    sort(a,i+1,right);
    return;
}